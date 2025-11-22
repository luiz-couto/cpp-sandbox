#include <iostream>
#include <print>
#include <vector>
#include "Math.h"

#include "GamesEngineeringBase.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_NAME "Triangle"

class Triangle {
    public:
    union {
        Vec4 v[3];
        struct { Vec4 v0, v1, v2; };
    };

    Triangle(Vec4 v0, Vec4 v1, Vec4 v2) : v0(v0), v1(v1), v2(v2) {}
};

float edgeFunction(const Vec4 &v0, const Vec4 &v1, const Vec4 &p) {
    return (((p.x - v0.x) * (v1.y - v0.y)) - ((v1.x - v0.x) * (p.y - v0.y)));
}

void findBounds(const Vec4 &v0, const Vec4 &v1, const Vec4 &v2, Vec4& tr, Vec4& bl){
    tr.x = min(max(max(v0.x, v1.x), v2.x), WINDOW_WIDTH - 1);
    tr.y = min(max(max(v0.y, v1.y), v2.y), WINDOW_HEIGHT - 1);
    bl.x = max(min(min(v0.x, v1.x), v2.x), 0);
    bl.y = max(min(min(v0.y, v1.y), v2.y), 0);
}

template<typename T>
T simpleInterpolateAttribute(T a0, T a1, T a2, float alpha, float beta, float gamma) {
    return (a0 * alpha) + (a1 * beta) + (a2 * gamma);
}

template<typename T>
T perspectiveCorrectInterpolateAttribute(
    T a0,
    T a1,
    T a2,
    float v0_w,
    float v1_w,
    float v2_w,
    float alpha,
    float beta,
    float gamma) {

        float frag_w = (alpha * v0_w) + (beta * v1_w) + (gamma * v2_w);
        T attrib[3];
        attrib[0] = a0 * alpha * v0_w;
        attrib[1] = a1 * beta * v1_w;
        attrib[2] = a2 * gamma * v2_w;
        return ((attrib[0] + attrib[1] + attrib[2]) / frag_w);
}

Vec4 transformPointToScreenSpace(Vec4 &point, float FOV, float zNear, float zFar) {
    Matrix m;

    m.setProjectionMatrix(zFar, zNear, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);
    Vec4 pc = m.mul(point);
    Vec4 pLine = pc.divideByW();

    float vx = ((pLine.x + 1) / 2) * WINDOW_WIDTH;
    float vy = ((pLine.y + 1) / 2) * WINDOW_HEIGHT;

    return Vec4(vx, vy, 0, 0);
} 

void draw(GamesEngineeringBase::Window &canvas, std::vector<Triangle*> triangles) {
    float FOV = 45;
    float zNear = 0.1;
    float zFar  = 1000;

    for (Triangle *triangle : triangles) {
        Vec4 tr, bl;
    
        Vec4 v0Projected = transformPointToScreenSpace(triangle->v0, FOV, zNear, zFar);
        Vec4 v1Projected = transformPointToScreenSpace(triangle->v1, FOV, zNear, zFar);
        Vec4 v2Projected = transformPointToScreenSpace(triangle->v2, FOV, zNear, zFar);
    
        findBounds(v0Projected, v1Projected, v2Projected, tr, bl);
    
        for (int y = (int)bl.y; y < (int)tr.y + 1; y++) {
            for (int x = (int)bl.x; x < (int)tr.x + 1; x++) {
                Vec4 p(x + 0.5f, y + 0.5f, 0, 0);
                // Compute triangle here
                Vec4 e0 = v1Projected - v0Projected;
                Vec4 e1 = v2Projected - v1Projected;
                Vec4 e2 = v0Projected - v2Projected;
    
                float alpha = edgeFunction(v1Projected, v0Projected, p);
                float beta = edgeFunction(v2Projected, v1Projected, p);
                float gamma = edgeFunction(v0Projected, v2Projected, p);
                float projArea = e0.x * e1.y - e0.y * e1.x;
                float area = 1.0f / projArea;
    
                alpha *= area;
                beta *= area;
                gamma *= area;
    
                if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
                    Colour frag = simpleInterpolateAttribute(Colour(1.0f, 0, 0), Colour(0, 1.0f, 0), Colour(0, 0, 1.0f),  alpha, beta, gamma);
                    canvas.draw(x, y, frag.r * 255, frag.g * 255, frag.b * 255);
                }
    
            }
        }
    }

}

void clip(const Vec4& v0, const Vec4& v1, const Vec4& v2, float d0, float d1, float d2, std::vector<Triangle>& out) {
    Vec4 verts[3]  = { v0, v1, v2 };
    float dist[3]  = { d0, d1, d2 };

    // Temporary arrays store indices
    int inside[3];
    int outside[3];
    int countInside = 0, countOutside = 0;

    for (int i = 0; i < 3; i++) {
        if (dist[i] >= 0)
            inside[countInside++] = i;
        else
            outside[countOutside++] = i;
    }

    // Case: all outside — return nothing
    if (countInside == 0) return;

    // Case: all inside — keep triangle
    if (countInside == 3) {
        out.push_back(Triangle(v0, v1, v2));
        return;
    }

    // Helper lambda for intersection
    auto intersect = [&](int i_in, int i_out)
    {
        float t = dist[i_in] / (dist[i_in] - dist[i_out]);
        return verts[i_in] + (verts[i_out] - verts[i_in]) * t;
    };

    if (countInside == 1 && countOutside == 2)
    {
        int i0 = inside[0];
        int o0 = outside[0];
        int o1 = outside[1];

        Vec4 A = verts[i0];
        Vec4 B = intersect(i0, o0);
        Vec4 C = intersect(i0, o1);

        out.push_back(Triangle(A, B, C));
    }
    else if (countInside == 2 && countOutside == 1)
    {
        int i0 = inside[0];
        int i1 = inside[1];
        int o0 = outside[0];

        Vec4 A = verts[i0];
        Vec4 B = verts[i1];
        Vec4 C = intersect(i0, o0);
        Vec4 D = intersect(i1, o0);

        out.push_back(Triangle(A, B, C));
        out.push_back(Triangle(B, D, C));
    }
}


std::vector<Triangle> clipping(std::vector<Triangle> triangles, float FOV, float zNear, float zFar) {
    Matrix m;
    m.setProjectionMatrix(zFar, zNear, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);

    Vec4 P2 = Vec4(m[8],  m[9],  m[10], m[11]);
    Vec4 P3 = Vec4(m[12], m[13], m[14], m[15]);

    Vec4 planeNear =  P2 + P3;
    Vec4 planeFar  = -P2 + P3;

    std::vector<Triangle> nearClipped;
    std::vector<Triangle> finalOut;

    // Pass 1: near plane
    for (auto& tri : triangles)
    {
        Vec4 a = m.mul(tri.v0);
        Vec4 b = m.mul(tri.v1);
        Vec4 c = m.mul(tri.v2);

        float da = planeNear.dot(a);
        float db = planeNear.dot(b);
        float dc = planeNear.dot(c);

        clip(a, b, c, da, db, dc, nearClipped);
    }

    // Pass 2: far plane
    for (auto& tri : nearClipped)
    {
        Vec4 a = tri.v0;
        Vec4 b = tri.v1;
        Vec4 c = tri.v2;

        float da = planeFar.dot(a);
        float db = planeFar.dot(b);
        float dc = planeFar.dot(c);

        clip(a, b, c, da, db, dc, finalOut);
    }

    return finalOut;
}


int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    bool running = true;

    float z = -1.0f;

    

    while (running)
    {
        // Check for input (key presses or window events)
        std::vector<Triangle*> triangles;
        Triangle triangle(
            Vec4(0.0f, 0.3f, z, 0.0f),
            Vec4(-0.3f, -0.3f, z, 0.0f),
            Vec4(0.3f, -0.3f, z, 0.0f)
        );
        triangles.push_back(&triangle);

        // Clear the window for the next frame rendering
        canvas.clear();

        // Update game logic
        draw(canvas, triangles);
        

        // Display the frame on the screen. This must be called once the frame
        //is finished in order to display the frame.
        canvas.present();

        z += 0.001f;
    }
    return 0;
}