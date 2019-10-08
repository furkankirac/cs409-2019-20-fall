#include <iostream>

// OOP:
// ctor/dtor
// copy-ctor, copy-assignment

// move-ctor, move-assignment
// inheritance

// unified/universal initialization

// namespaces
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword)

// std::vector

template<typename T = int>
struct Vector
{
    size_t size;
    T* values = nullptr;

    Vector() : size(0), values(nullptr) // default ctor
    {
    }

//    Vector(int size) : size(size), values(new int[size]) { }
    Vector(int size) { init(size); }

    Vector(const Vector& other)
    {
        *this = other;
    }

    ~Vector() { release(); }

    void init(int size_)
    {
        release();

        size = size_;
        values = new T[size];
    }

    void release()
    {
        delete[] values;
        values = nullptr;
        size = 0;
    }

    void operator=(const Vector& vright) // copy assignment
    {
//        Vector& vleft = *this;
        init(vright.size);
        for(int i=0; i<size; ++i)
            values[i] = vright.values[i];
    }

    T& operator[](size_t index)
    {
        return values[index];
    }
};

// explicit template instantiation
//template struct Vector<float>;


int main(int argc, char* argv[])
{
    auto v1 = Vector<int>{5}; // 5 integer storage allocated
    auto v2 = Vector<int>{10}; // 10 integer storage allocated

    v1 = v2; // copy assignment

    Vector<int> v3{v1}; // copy ctor
    Vector<int> v4 = v1; // copy ctor
    Vector<int> v5; // default ctor
    v5 = v1; // copy assignment

    Vector<float> f1{5}; // alocate mem for 5 floats
    f1.values[0] = 3.14;
    f1[0] = 3.14;

    std::cout << v1.size << std::endl;

    return 0;
}
