// std::move, perfect forwarding, std::forward
// TypeDisplayer trick
// if constexpr

#include <iostream>
#include <vector>


struct Foo
{
    int value1, value2;

    Foo() : value1{}, value2{} {
        std::cout << "default c-tor." << std::endl;
    }
    Foo(int value1) : value1{value1}, value2{} {
        std::cout << "c-tor with 1 int." << std::endl;
    }
    Foo(int value1, int value2) : value1{value1}, value2{value2} {
        std::cout << "c-tor with 2 ints." << std::endl;
    }

    Foo(std::initializer_list<int> il) : value1{il.begin()[0]}, value2{il.begin()[1]}
    {
        std::cout << "init list. c-tor" << std::endl;
    }
};


int main(int argc, char* argv[])
{
    auto foo1 = Foo{};
    auto foo2 = Foo(1);
    auto foo3 = Foo(1, 2);
    auto foo4 = Foo{1, 2, 3};
    return 0;
}
