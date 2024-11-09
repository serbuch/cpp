#include <iostream>

template<typename T>
T pow(T a, T b) {
    if (a < 0) 
        throw nan;
    if (b < 0)
        return 1/pow(a, -b);
    return pow(a, b);
}

int main() {
    std::cout << pow(-2.,-3.14) << std::endl;
}