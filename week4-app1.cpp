#include <iostream>
#include <vector>
#include <string>

// Matrix class, Image class inherited from Matrix
// printMatrix
// function pointers, function objects, lambdas

struct ColoredPixel
{
    unsigned char r, g, b;

    operator const char *() const
    {
        static std::string s = "";
        s = std::string("RGB=") +
                std::to_string((int)r) + "," +
                std::to_string((int)g) + "," +
                std::to_string((int)b);
        return s.c_str();
    }
};

template<typename T>
class Matrix
{
    size_t num_rows;
    size_t num_cols;

    std::vector<T> data;

public:
    Matrix() : num_rows{}, num_cols{}, data{} { }

    Matrix(size_t num_rows, size_t num_cols) :
        num_rows(num_rows),
        num_cols(num_cols),
        data(num_rows*num_cols)
    {
//        for(size_t i=0; i<num_rows; ++i)
//            for(size_t j=0; j<num_cols; ++j)
//                (*this)(i, j) = 0;
    }

//    ~Matrix() { delete[] data; }

//    Matrix(const Matrix<T>& other) :
//        num_rows(other.num_rows),
//        num_cols(other.num_cols),
//        data(other.data)
//    {
//        std::cout << "Copy ctor has been called." << std::endl;
//    }

//    void operator=(const Matrix<T>& other)
//    {
//        num_rows = other.num_rows;
//        num_cols = other.num_cols;
//        data = other.data;
//        std::cout << "Copy assign has been called." << std::endl;
//    }

    void print() const
    {
        for(size_t i=0; i<num_rows; ++i)
        {
            for(size_t j=0; j<num_cols; ++j)
                std::cout << (*this)(i, j) << ", ";
            std::cout << std::endl;
        }
    }

    const T& operator()(size_t row, size_t col) const { return data[row*num_cols + col]; }
    T& operator()(size_t row, size_t col) { return data[row*num_cols + col]; }
};


//typedef Matrix<ColoredPixel> ColoredImage;
//using ColoredImage = Matrix<ColoredPixel>;

class ColoredImage : public Matrix<ColoredPixel>
{
//    ColoredImage(size_t num_rows, size_t num_cols) :
//        Matrix<ColoredPixel>(num_rows, num_cols)
//    {
//    }

//    void operator=(const ColoredImage& other)
//    {
//        Matrix<ColoredPixel>::operator=(other);
//    }

    using Matrix<ColoredPixel>::Matrix;
    using Matrix<ColoredPixel>::operator=;
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

//    auto img0 = Matrix<ColoredPixel>(100, 100);
    auto img1 = ColoredImage(3, 3);

    img1(2, 2) = ColoredPixel{10, 100, 200};

    img1.print();

//    std::cout << m1(1, 1) << std::endl;
    return 0;
}



//    int a[3] = {1, 2, 3};
//    std::cout << a[2] << std::endl;
//    std::cout << *(a + 2) << std::endl;
//    std::cout << *(2 + a) << std::endl;
//    std::cout << 2[a] << std::endl;

