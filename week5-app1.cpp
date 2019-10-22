#include <iostream>
#include <vector>
#include <string>

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
    size_t          m_num_rows;
    size_t          m_num_cols;
    std::vector<T>  m_data;

public:
    Matrix() : m_num_rows{}, m_num_cols{}, m_data{} { }
    Matrix(size_t num_rows, size_t num_cols) : m_num_rows(num_rows), m_num_cols(num_cols), m_data(num_rows*num_cols) { }

    const T& operator()(size_t row, size_t col) const { return m_data[row*m_num_cols + col]; }
    T& operator()(size_t row, size_t col) { return m_data[row*m_num_cols + col]; }

    size_t num_rows() const { return m_num_rows; }
    size_t num_cols() const { return m_num_cols; }
};

class ColoredImage : public Matrix<ColoredPixel>
{
    using Matrix<ColoredPixel>::Matrix;
    using Matrix<ColoredPixel>::operator=;
};

// function pointer version
using print_with_style_t = void (*)(const char*);

template<typename T>
void print_v1(const Matrix<T>& m, print_with_style_t printer)
{
    auto num_rows = m.num_rows();
    auto num_cols = m.num_cols();
    for(size_t i=0; i<num_rows; ++i)
    {
        for(size_t j=0; j<num_cols; ++j)
            printer(m(i, j));

        std::cout << std::endl;
    }
}

void print_with_styleA(const char* s) { std::cout << s << ", "; }
void print_with_styleB(const char* s) { std::cout << s << "|"; }

// function object version
struct PrintWithStyleA
{
    void operator()(const char* s) const { std::cout << s << ", "; }
};

struct PrintWithStyleB
{
    void operator()(const char* s) const { std::cout << s << "|"; }
};

template<typename T, typename PRINTER>
void print_v2(const Matrix<T>& m, PRINTER printer)
{
    auto num_rows = m.num_rows();
    auto num_cols = m.num_cols();
    for(size_t i=0; i<num_rows; ++i)
    {
        for(size_t j=0; j<num_cols; ++j)
            printer(m(i, j));

        std::cout << std::endl;
    }
}

//template class Matrix<float>; // explicit template instantiation for T=float


int main(int argc, char* argv[])
{
    auto img = ColoredImage(3, 3);
    img(2, 2) = ColoredPixel{10, 100, 200};

    // function pointer version
    print_v1(img, &print_with_styleA);
    print_v1(img, &print_with_styleB);

    // function object version
    auto printer1 = PrintWithStyleA{}; // create an instance of PrintWithStyleA
    auto printer2 = PrintWithStyleB{}; // create an instance of PrintWithStyleA
    printer1("Hello");
    printer2("World");
    print_v2(img, PrintWithStyleA{});
    print_v2(img, PrintWithStyleB{});

    // lambda version without creating structs. lambda does create it automatically
    // lambda functions are by default const
    // to make them writable, you can write "mutable" at the end
    print_v2(img, [](const char* s) { std::cout << s << ", "; });
    print_v2(img, [](const char* s) { std::cout << s << "|"; });

    return 0;
}
