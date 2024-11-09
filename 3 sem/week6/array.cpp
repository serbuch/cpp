#include <iostream>

template <typename T, unsigned N>
class Array
{
public:
    explicit Array(const T&): data(new T[N]) {};
    
    Array(const Array & arr): data(arr->data) {};
    
    ~Array() {
        delete[] data;
    }
    
    Array& operator=(const Array &other) {
        if (this != &other) {
            delete[] data;

            data = other.data;
        }
        return *this;
    };
    T& operator[](unsigned id) {
        if (id >= N) {
            throw std::out_of_range("Index out of range!");
        }
        return data[id];
    }

    size_t size() const {
        return N;
    }

    T& front() {
        return data[0];
    }

    T& back() {
        return data[N-1];
    }

    bool empty() {
        for (int i = 0; i < N; i++) {
            if (data[i] != T() )
                return false;  
        }
        return true;
    }

    void fill(const T& value) {
        for (int i = 0; i < N; i++)
            data[i] = value;
    }

private:
    T* data;
};

int main() {
    std::cout << "hi" << std::endl;
    int a;
    Array<int, 7> arr(a);
    std::cout << arr.size() << std::endl;
    std::cout << arr.empty() << '\n';
    arr.fill(9);
    std::cout << arr.empty() << '\n';
    std::cout << arr.front() << '\n';
    std::cout << arr.back() << '\n';
    for (int i = 0; i < 7; i++) {
        std::cout << arr[i] << std::endl;
    }
};