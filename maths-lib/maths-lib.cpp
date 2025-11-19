#include <iostream>
#include <print>
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

void draw(GamesEngineeringBase::Window &canvas, Triangle& triangle) {
    Vec4 tr, bl;
    findBounds(triangle.v0, triangle.v1, triangle.v2, tr, bl);

    for (int y = (int)bl.y; y < (int)tr.y + 1; y++) {
        for (int x = (int)bl.x; x < (int)tr.x + 1; x++) {
            Vec4 p(x + 0.5f, y + 0.5f, 0, 0);
            // Compute triangle here
            Vec4 e0 = triangle.v1 - triangle.v0;
            Vec4 e1 = triangle.v2 - triangle.v1;
            Vec4 e2 = triangle.v0 - triangle.v2;

            float alpha = edgeFunction(triangle.v1, triangle.v0, p);
            float beta = edgeFunction(triangle.v2, triangle.v1, p);
            float gamma = edgeFunction(triangle.v0, triangle.v2, p);

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

int main() {
    GamesEngineeringBase::Window canvas;
    canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
    bool running = true;

    Triangle triangle(
        Vec4(100.0f, 100.0f, 0.0f, 0.0f),
        Vec4(400.0f, 300.0f, 0.0f, 0.0f),
        Vec4(200.0f, 500.0f, 0.0f, 0.0f)
    );

    Triangle triangle2(
        Vec4(600.0f, 100.0f, 0.0f, 0.0f),
        Vec4(900.0f, 300.0f, 0.0f, 0.0f),
        Vec4(700.0f, 500.0f, 0.0f, 0.0f)
    );

    while (running)
    {
        // Check for input (key presses or window events)


        // Clear the window for the next frame rendering
        canvas.clear();

        // Update game logic
        draw(canvas, triangle);
        draw(canvas, triangle2);
        

        // Display the frame on the screen. This must be called once the frame
        //is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}