#include "include/my_math.hpp"
#include <iostream>
#include <cmath>

int main() {
    std::cout << my_sin(M_PI/2).val_x << "\n";
    std::cout << my_cos(M_PI/2).val_x << "\n";
    std::cout << my_tan(M_PI/2).val_x << "\n";
    std::cout << my_ctan(M_PI/4).val_x << std::endl;
}
