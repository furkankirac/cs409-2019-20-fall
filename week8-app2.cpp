// lambda captures, mutable lambdas and equivalent classes
// if constexpr
// lvalue, rvalue
// TypeDisplayer trick
// std::move, perfect forwarding, std::forward

#include <iostream>

struct Lambda0
{
    int offset;
    int& mult;
    int value = 0;

    Lambda0(int& mult, int offset) : mult{mult}, offset{offset} { }

    auto operator() () {
        return offset + mult * value++;
    }
};


int main(int argc, char* argv[])
{
    auto mult = 100;
    auto offset = 5;

    auto l1 = [value=0, &mult, offset]() mutable {
        return offset + mult * value++;
    };
    std::cout << l1() << std::endl;
    std::cout << l1() << std::endl;
    std::cout << l1() << std::endl;

    mult = 1000;
    offset = 6;
    std::cout << l1() << std::endl;
    std::cout << l1() << std::endl;
    std::cout << l1() << std::endl;

    return 0;
}
