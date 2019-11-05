// inline keyword
// comma operator

// one type of functional programming example in C++: template specializations

#include <iostream>

inline int print()
{
    static int value = 0;

    std::cout << "Hello" << std::endl;
    return ++value;
}

int main(int argc, char* argv[])
{
    std::cout << print() << std::endl;
    std::cout << print() << std::endl;
    std::cout << print() << std::endl;

    auto value = (print(), print(), print());
    std::cout << value << std::endl;
    return 0;
}
