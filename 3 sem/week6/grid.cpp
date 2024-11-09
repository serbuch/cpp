#include <vector>
#include <cassert>
#include <array>
#include <iostream>

// Class for managing multi-dimensional grids
template<typename T, unsigned N>
class Grid {
    static_assert(N > 0, "Grid must have at least one dimension.");
    
    using size_type = unsigned;
    std::vector<T> data;
    std::array<size_type, N> sizes;
    
    // Helper to calculate total size of the grid
    size_type totalSize() const {
        size_type total = 1;
        for (size_type size : sizes) {
            total *= size;
        }
        return total;
    }

public:
    Grid() = default;

    template<typename... Args>
    Grid(size_type size, Args... args) : sizes{size, static_cast<size_type>(args)...} {
        static_assert(sizeof...(args) == N - 1, "Number of arguments must match grid dimensions.");
        data.resize(totalSize());
    }

    Grid(size_type size, T const& t) : sizes{size, 1} {
        data.resize(size, t);
    }

    // Access elements (N-dimensional index unpacking)
    template<typename... Args>
    T& operator()(size_type index, Args... indices) {
        size_type idx = index;
        size_type stride = sizes[0];
        size_type computedIndex = idx;
        
        for (unsigned i = 1; i < N; ++i) {
            idx = (i < sizeof...(indices) + 1 ? *(size_type[]){indices...} : idx);
            computedIndex = computedIndex * stride + idx;
            stride = sizes[i];
        }
        return data[computedIndex];
    }
    
    // Const overload
    template<typename... Args>
    T const& operator()(size_type index, Args... indices) const {
        return const_cast<Grid*>(this)->operator()(index, indices...);
    }
    
    // Indexing for reduced dimensions
    Grid<T, N-1> operator[](size_type index) const {
        return Grid<T, N-1>(&data[index * totalSize() / sizes[0]], sizes[1]);
    }

    // Assign all elements to a value
    Grid& operator=(T const& t) {
        std::fill(data.begin(), data.end(), t);
        return *this;
    }

    size_type size(unsigned dimension) const {
        return sizes[dimension];
    }
};

// Specialization for 1D Grid
template<typename T>
class Grid<T, 1> {
    using size_type = unsigned;
    std::vector<T> data;

public:
    Grid(size_type size, T const& t = T()) : data(size, t) { }

    T& operator()(size_type index) {
        return data[index];
    }
    T const& operator()(size_type index) const {
        return data[index];
    }
    
    Grid& operator=(T const& t) {
        std::fill(data.begin(), data.end(), t);
        return *this;
    }
    
    size_type size(unsigned dimension = 0) const {
        return data.size();
    }
};

// Examples
int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    for (unsigned int y = 0; y < g2.size(0); ++y)
    for (unsigned int x = 0; x < g2.size(1); ++x)
        std::cout << g2(y, x) << " ";
    
    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    return 0;
}