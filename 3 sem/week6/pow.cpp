#include <iostream>

template<unsigned M, unsigned N>
struct Pow;

template<unsigned M>
struct Pow<M, 1> {
    static const long long value = M;
};

template<unsigned M, unsigned N>
struct Pow {
    static const long long value = Pow<M, N - 1>::value * M;
};


int main() {
    std::cout << Pow<2,30>::value << std::endl;
}