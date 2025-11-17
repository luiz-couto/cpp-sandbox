#include <iostream>
#include <print>
#include "Math.h"

int main(){
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(4.0f, 5.0f, 6.0f);

    Vec3 c = a + b;
    Vec3 d = a * b;
    Vec3 e = a + 10.0f;
    Vec3 f = b * 2.0f;

    std::println("{}", c);
    std::println("{}", d);
    std::println("{}", e);
    std::println("{}", f);

    Vec4 u(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4 v(5.0f, 6.0f, 7.0f, 8.0f);

    Vec4 w = u + v;
    Vec4 x = u * v;

    std::println("{}", w);
    std::println("{}", x);

    return 0;
}