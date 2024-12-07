#include <iostream>
#include <cassert>


template<typename T, unsigned Dim>
class Grid;

template<typename T>
class Grid<T, 1> final {

public:
    using value_type = T;
    using size_type = unsigned;
private:
    value_type* data;
    size_type size;
public:
    Grid(): data(nullptr), size(0) {}
    Grid(value_type const &t): data(new value_type[1]), size(1) {data[0] = t;}
    Grid(size_type size): size(size), data(new value_type[size]) {}
    Grid(size_type size, value_type const &t):size(size), data(new value_type[size]) {
        for (int i = 0; i < size; i++)
            data[i] = t;
    }
    Grid(value_type *data , size_type size): data(data), size(size) {}
    ~Grid() {
        delete[] data;
        data = nullptr;
        size = 0;
    }

    Grid(Grid<value_type, 1> const& other): size(other.size) {
        data = new value_type[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }
    Grid(Grid<value_type, 1>&& other): size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
    }

    Grid<value_type, 1>& operator=(Grid<value_type, 1>& other) {
        if (this != &other) {
            value_type *newData = new value_type[other.size];
            for (int i = 0; i < size; i++)
                newData[i] = other.data[i];

            delete[] data;
            data = newData;
            size = other.size;
        }
        return *this;
    }

    Grid<value_type, 1>& operator=(Grid<value_type, 1>&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    };

    const value_type& operator()(size_type idx) const {
        if (idx >= size) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[idx];
    }

    value_type& operator()(size_type idx) {
        if (idx >= size) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[idx];
    }

    value_type& operator[](size_type idx) {
        if (idx >= size) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[idx];
    }
    const value_type& operator[](size_type idx) const {
        if (idx >= size) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[idx];
    }

    size_type get_size() const { 
        return size; 
    }
};


template<typename T, unsigned Dim>
class Grid final {

public:
    static_assert(Dim > 0);
    using value_type = T;
    using size_type = unsigned;
private:
    Grid<value_type, Dim - 1>* data;
    size_type size;
public:
    Grid(): data(nullptr), size(0) {}
    template<typename Head, typename ... Tail>
    Grid(Head head, Tail ... tail): size(head) {
        data = new Grid<value_type,Dim - 1>[head];
        for (size_type i = 0; i < head; i++) {
            data[i] = Grid<value_type, Dim - 1>(tail ...);
        }
    }
    Grid(Grid<value_type, Dim> const& other) {
        size = other.size;
        data = new Grid<value_type, Dim - 1>[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }
    Grid(Grid<value_type, 1>&& other): size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
    }
    
    Grid<value_type, Dim - 1>& operator[](size_type idx) {
        return data[idx];
    }

    const Grid<value_type, Dim - 1>& operator[](size_type idx) const {
        return data[idx];
    }
    
    Grid<value_type, Dim>& operator=(const Grid<value_type, Dim>& other) {
        if (this != &other) {
            // copy and swap
            auto tmp = other;
            // Grid<value_type, Dim - 1> *newData = new Grid<value_type, Dim - 1>[other.size];
            // for (int i = 0; i < size; i++)
                // newData[i] = other.data[i];
            std::swap(tmp.size, size);
            std::swap(tmp.data, data);
            // delete[] data;
            // data = newData;
            // size = other.size;
        }
        return *this;
    }

    Grid<value_type, Dim>& operator=(Grid<value_type, Dim>&& other) {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;

            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    };

    template<typename Head, typename ... Tail>
    value_type& operator()(Head head, Tail ... tail) {
        if (head >= size) {
            throw std::out_of_range("Grid index out of range");
        }
        return data[head](tail...);
    }

    // Grid<int, 1> get_size() {
    //     Grid<int, 1> sizes(Dim);
    //     sizes.data[0] = size;
    //     sizes.data[1] = data[0].size;
    //     sizes.data[2] = data[0][0].size;
    //     for (int i = 1, i < Dim; i ++)
    //         sizes.data[i] = data[0].size;
    //         sizes.data[i + 1] = data[0].get_size();

    // }
    
    ~Grid() {
        delete[] data;
        data = nullptr;
        size = 0;
    }
};


int main() {

    // Grid<float, 2> g(3, 2, 0.0f);
    // assert(3 == g.get_y_size());
    // assert(2 == g.get_x_size());

    // using gsize_t = Grid<int>::size_type;

    // for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    // for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    //     assert(0.0f == g[y_idx][x_idx]);

    // for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    // for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    //     g[y_idx][x_idx] = 1.0f;

    // for(gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
    // for(gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
    //     assert(1.0f == g(y_idx , x_idx));
    // return 0;

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2[1][1]);
    assert(2.0f == g2(1,1));

    Grid<float, 1> g(2, 2.0f);
    assert(2.0f == g[0]);

    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3[0][0][0]);
    g3.~Grid();


    // g2 = g3[1];
    // assert(1.0f == g2[1][1]);

    // const Grid<float, 3> cg(1,2,3,3.14);
}