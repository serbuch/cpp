#include <iostream>
#include <string>
#include <fstream>
#include "vec3.hpp"

using color = Vec3;

void write_color(std::ostream& out, const color& pixel_color) {
    out << static_cast<int>(pixel_color.x()) << ' ' 
    << static_cast<int>(pixel_color.y()) << ' ' 
    << static_cast<int>(pixel_color.z()) 
    << '\n';
}

void write_image(int width, int height) {
    
    std::string path("my_image.ppm");
    std::ofstream os(path);

    os << "P3\n" << width << ' ' << height << "\n255\n";

    Vec3 vec;

    for (int j = 0; j < height; j++)
    {
        std::clog << "\rScanlines remaining: " << (height - j) << ' ' << std::flush;
        for (int i = 0; i < width; i++)
        {
            // transform [0, 1] to rgb color channels
            auto r = double(i) / (width-1);
            auto g = double(j) / (height-1);
            auto b = 0.0;

            vec = Vec3(r*255.999, g*255.999, b*255.999);
            // end of transform

            write_color(os, vec);
        }
    }
    std::clog << "\rDone.                    \n";
}