#include <iostream>

// Matrix class, Image class inherited from Matrix
// printMatrix
// function pointers, function objects, lambdas


template<typename T>
class Matrix
{
    size_t num_rows;
    size_t num_cols;

    T* data;

public:
    Matrix() : num_rows(0), num_cols(0), data(nullptr) { }

    Matrix(size_t num_rows, size_t num_cols) :
        num_rows(num_rows),
        num_cols(num_cols),
        data(new T[num_rows*num_cols])
    {
        for(size_t i=0; i<num_rows; ++i)
            for(size_t j=0; j<num_cols; ++j)
                (*this)(i, j) = 0;
    }

    ~Matrix() { delete[] data; }

    Matrix(const Matrix<T>& other) :
        num_rows(other.num_rows),
        num_cols(other.num_cols),
        data(new T[other.num_rows*other.num_cols])
    {
        std::cout << "Copy ctor has been called." << std::endl;
        for(size_t i=0; i<num_rows; ++i)
            for(size_t j=0; j<num_cols; ++j)
                (*this)(i, j) = other(i, j);
    }

    void operator=(const Matrix<T>& other)
    {
        num_rows = other.num_rows;
        num_cols = other.num_cols;
        data = new T[other.num_rows*other.num_cols];
        std::cout << "Copy assign has been called." << std::endl;
        for(size_t i=0; i<num_rows; ++i)
            for(size_t j=0; j<num_cols; ++j)
                (*this)(i, j) = other(i, j);
    }


    void print() const
    {
        for(size_t i=0; i<num_rows; ++i)
        {
            for(size_t j=0; j<num_cols; ++j)
                std::cout << (*this)(i, j) << ", ";
            std::cout << std::endl;
        }
    }

    T& operator()(size_t row, size_t col) const { return data[row*num_cols + col]; }
    T& operator()(size_t row, size_t col) { return data[row*num_cols + col]; }


};


int main(int argc, char* argv[])
{
    auto m1 = Matrix<int>(3, 2);
    auto m2 = Matrix<int>();

    m1(0, 0) = 1000;
    m1(2, 1) = 2000;

    auto m3 = m1;
    m1(0, 0) = 1;
    m1.print();
    m3.print();

    m3 = m2;
    m3.print();


//    std::cout << m1(1, 1) << std::endl;
    return 0;
}



//    int a[3] = {1, 2, 3};
//    std::cout << a[2] << std::endl;
//    std::cout << *(a + 2) << std::endl;
//    std::cout << *(2 + a) << std::endl;
//    std::cout << 2[a] << std::endl;

