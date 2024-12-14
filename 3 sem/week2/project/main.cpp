#ifndef WIDTH
#define WIDTH 480
#endif

#ifndef HEIGHT
#define HEIGHT 320
#endif

#include <iostream>
#include "utils.hpp"
#include "vec3.hpp"

int main()
{
    write_image(WIDTH, HEIGHT);
    Vec3 vec1(1.,2.,3.), vec2;
    std::cout << vec1.print() << vec2.print() << std::endl;
}