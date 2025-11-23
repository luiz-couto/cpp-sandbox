#include <iostream>
#include <print>
#include <vector>
#include "Math.h"

#include "GamesEngineeringBase.h"
#include "GEMLoader.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_NAME "Triangle"

class Triangle {
    public:
    union {
        Vec4 v[3];
        struct { Vec4 v0, v1, v2; };
    };
    union {
        Vec3 n[3];
        struct { Vec3 n0, n1, n2; };
    };

    Triangle(
        Vec4 v0,
        Vec4 v1,
        Vec4 v2,
        Vec3 n0,
        Vec3 n1,
        Vec3 n2
    ) : v0(v0), v1(v1), v2(v2), n0(n0), n1(n1), n2(n2) {}
};

class Camera {
    public:
    Vec3 from;
    Vec3 to;
    Vec3 up;

    Camera() : from(0, 0, 0.5f), to(0, 0, 0), up(0, -1, 0) {}
    Camera(Vec3 from, Vec3 to, Vec3 up) : from(from), to(to), up(up) {}
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

    return Vec4(vx, vy, pLine.z, pLine.w);
}

void clip(
    const Vec4& v0, const Vec4& v1, const Vec4& v2,
    const Vec3& n0, const Vec3& n1, const Vec3& n2,
    float d0, float d1, float d2,
    std::vector<Triangle*> &out)
{
    Vec4  verts[3]  = { v0, v1, v2 };
    Vec3  norms[3]  = { n0, n1, n2 };
    float dist[3]   = { d0, d1, d2 };

    int inside[3], outside[3];
    int countInside = 0, countOutside = 0;

    for (int i = 0; i < 3; i++)
    {
        if (dist[i] >= 0) inside[countInside++] = i;
        else outside[countOutside++] = i;
    }

    // All outside → discard
    if (countInside == 0) return;

    // All inside → keep as is
    if (countInside == 3)
    {
        out.push_back(new Triangle(
            v0, v1, v2,
            n0, n1, n2
        ));
        return;
    }

    // Intersection helper
    auto intersectV = [&](int i_in, int i_out)
    {
        float t = dist[i_in] / (dist[i_in] - dist[i_out]);
        return verts[i_in] + (verts[i_out] - verts[i_in]) * t;
    };

    auto intersectN = [&](int i_in, int i_out)
    {
        float t = dist[i_in] / (dist[i_in] - dist[i_out]);
        Vec3 result = norms[i_in] + (norms[i_out] - norms[i_in]) * t;
        return result.normalize();
    };

    // One inside → 1 output triangle
    if (countInside == 1)
    {
        int i0 = inside[0];
        int o0 = outside[0];
        int o1 = outside[1];

        Vec4 A = verts[i0];
        Vec4 B = intersectV(i0, o0);
        Vec4 C = intersectV(i0, o1);

        Vec3 nA = norms[i0];
        Vec3 nB = intersectN(i0, o0);
        Vec3 nC = intersectN(i0, o1);

        out.push_back(new Triangle(A, B, C, nA, nB, nC));
    }

    // Two inside → 2 output triangles
    else if (countInside == 2)
    {
        int i0 = inside[0];
        int i1 = inside[1];
        int o0 = outside[0];

        Vec4 A = verts[i0];
        Vec4 B = verts[i1];
        Vec4 C = intersectV(i0, o0);
        Vec4 D = intersectV(i1, o0);

        Vec3 nA = norms[i0];
        Vec3 nB = norms[i1];
        Vec3 nC = intersectN(i0, o0);
        Vec3 nD = intersectN(i1, o0);

        // Triangle 1: A, B, C
        out.push_back(new Triangle(A, B, C, nA, nB, nC));

        // Triangle 2: B, D, C
        out.push_back(new Triangle(B, D, C, nB, nD, nC));
    }
}


std::vector<Triangle*> clipping(std::vector<Triangle*> triangles, float FOV, float zNear, float zFar) {
    Matrix m;
    m.setProjectionMatrix(zFar, zNear, FOV, WINDOW_WIDTH, WINDOW_HEIGHT);

    Vec4 P2 = Vec4(m[8], m[9], m[10], m[11]);
    Vec4 P3 = Vec4(m[12], m[13], m[14], m[15]);

    Vec4 planeNear = P2 + P3;
    Vec4 planeFar  = -P2 + P3;

    std::vector<Triangle*> nearClipped;
    std::vector<Triangle*> finalOut;

    // Pass 1: near plane
    for (auto& tri : triangles) {   
        Vec4 a = m.mul(tri->v0);
        Vec4 b = m.mul(tri->v1);
        Vec4 c = m.mul(tri->v2);

        float da = planeNear.dot(a);
        float db = planeNear.dot(b);
        float dc = planeNear.dot(c);

        clip(a, b, c, tri->n0, tri->n1, tri->n2, da, db, dc, nearClipped);
    }

    // Pass 2: far plane
    for (auto& tri : nearClipped) {
        Vec4 a = tri->v0;
        Vec4 b = tri->v1;
        Vec4 c = tri->v2;

        float da = planeFar.dot(a);
        float db = planeFar.dot(b);
        float dc = planeFar.dot(c);

        clip(a, b, c, tri->n0, tri->n1, tri->n2, da, db, dc, finalOut);
    }

    return finalOut;
}


std::vector<Triangle*> transformTrianglesToViewSpace(Camera &camera, std::vector<Triangle*> &triangles) {
    Matrix viewMatrix;
    viewMatrix.setLookatMatrix(camera.from, camera.to, camera.up);

    std::vector<Triangle*> transformedTriangles;

    for (Triangle* tri : triangles) {
        Vec4 v0 = viewMatrix.mul(tri->v0);
        Vec4 v1 = viewMatrix.mul(tri->v1);
        Vec4 v2 = viewMatrix.mul(tri->v2);

        transformedTriangles.push_back(new Triangle(
            v0, v1, v2,
            tri->n0,
            tri->n1,
            tri->n2
        ));
    }
    return transformedTriangles;
}

void simpleShading(const Triangle& triangle, const Vec4& p, Colour& outColour, Vec3 &normal) {
    float PI = 3.1415f;
    Vec4 e0 = triangle.v1 - triangle.v0;
    Vec4 e1 = triangle.v2 - triangle.v1;

    Vec3 N = normal.normalize();

    Vec3 omega_i = Vec3(1, 1, 0).normalize();
    Colour rho(0, 1.0f, 0);
    Colour L(1.0f, 1.0f, 1.0f);
    Colour ambient(0.5f, 0.5f, 0.5f);

    float NdotL = max(N.x * omega_i.x + N.y * omega_i.y + N.z * omega_i.z, 0.0f);
    outColour = (rho / PI) * (L * NdotL + ambient);
}


void draw(GamesEngineeringBase::Window &canvas, Camera &camera, std::vector<Triangle*> &triangles) {
    float FOV = 45;
    float zNear = 0.1;
    float zFar  = 1000;

    std::vector<Triangle*> transformedTriangles = transformTrianglesToViewSpace(camera, triangles);
    //std::vector<Triangle*> clippedTriangles = clipping(triangles, FOV, zNear, zFar);

    float* zBuffer = new float[WINDOW_WIDTH * WINDOW_HEIGHT];
    for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
        zBuffer[i] = 1;
    }

    for (Triangle *triangle : transformedTriangles) {
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

                float z = v0Projected.z * alpha + v1Projected.z * beta + v2Projected.z * gamma;
    
                if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1) {
                    if (z < zBuffer[y * WINDOW_WIDTH + x]) {
                        
                        zBuffer[y * WINDOW_WIDTH + x] = z;
                        
                        // Colour frag = perspectiveCorrectInterpolateAttribute<Colour>(
                        //     Colour(0.0f, 0.1f, 0.9f),
                        //     Colour(0.0f, 0.1f, 0.9f),
                        //     Colour(0.0f, 0.1f, 0.9f),
                        //     triangle->v0.w,
                        //     triangle->v1.w,
                        //     triangle->v2.w,
                        //     alpha,
                        //     beta,
                        //     gamma
                        // );

                        Colour frag;

                        Vec3 normal = perspectiveCorrectInterpolateAttribute<Vec3>(
                            triangle->n0,
                            triangle->n1,
                            triangle->n2,
                            triangle->v0.w,
                            triangle->v1.w,
                            triangle->v2.w,
                            alpha,
                            beta,
                            gamma
                        );

                        simpleShading(*triangle, p, frag, normal);
                        canvas.draw(x, y, frag.r * 255, frag.g * 255, frag.b * 255);
                    }
                }
            }
        }
    }
    delete[] zBuffer;
}

int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    bool running = true;

    float z = -1.0f;

    std::vector<GEMLoader::GEMMesh> gemmeshes;
    GEMLoader::GEMModelLoader loader;
    loader.load("assets/bunny.gem", gemmeshes);

    std::vector<Triangle*> trianglesList;
    for (int i = 0; i < gemmeshes.size(); i++) {
        for (int j = 0; j < gemmeshes[i].indices.size(); j = j + 3) {
            GEMLoader::GEMVec3 vec1;
            GEMLoader::GEMVec3 norm1;
            int index = gemmeshes[i].indices[j];
            vec1 = gemmeshes[i].verticesStatic[index].position;
            norm1 = gemmeshes[i].verticesStatic[index].normal;

            GEMLoader::GEMVec3 vec2;            
            GEMLoader::GEMVec3 norm2;
            int index2 = gemmeshes[i].indices[j + 1];
            vec2 = gemmeshes[i].verticesStatic[index2].position;
            norm2 = gemmeshes[i].verticesStatic[index2].normal;

            GEMLoader::GEMVec3 vec3;            
            GEMLoader::GEMVec3 norm3;
            int index3 = gemmeshes[i].indices[j + 2];
            vec3 = gemmeshes[i].verticesStatic[index3].position;
            norm3 = gemmeshes[i].verticesStatic[index3].normal;
            
            Triangle* triangle = new Triangle(
                Vec4(vec1.x, vec1.y, vec1.z, 1.0f),
                Vec4(vec2.x, vec2.y, vec2.z, 1.0f),
                Vec4(vec3.x, vec3.y, vec3.z, 1.0f),
                Vec3(norm1.x, norm1.y, norm1.z),
                Vec3(norm2.x, norm2.y, norm2.z),
                Vec3(norm3.x, norm3.y, norm3.z)
            );
            trianglesList.push_back(triangle);
        }
    }

    GamesEngineeringBase::Timer tim = GamesEngineeringBase::Timer();
    float radius = 0.5f;
    float time = 0.0f;
    Camera camera;

    while (running)
    {
        // Check for input (key presses or window events)
        float dt = tim.dt();
        time += dt;

        Vec3 from = Vec3(radius * cos(time), 0, radius * sinf(time));
        camera.from = from;

        // Clear the window for the next frame rendering
        canvas.clear();

        // Update game logic
        draw(canvas, camera, trianglesList);
        
        // Display the frame on the screen. This must be called once the frame
        //is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}