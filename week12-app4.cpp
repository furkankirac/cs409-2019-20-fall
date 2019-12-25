#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

// advanced corner cases:
// - template template parameters

// - std::invoke_result

// - std::declval: simulation of instance creations in unevaluated contextes.
// i.e., find data type pointed by an iterator, first by a function template, then by a class template

template<typename ...> struct TD;

template<template<typename...> typename Container, typename First, typename Second>
void print_container(const Container<First, Second>& container)
{
    if constexpr(std::is_same_v< Container<int, int>, std::vector<int, int> >)
    {
        std::cout << "std::vector version" << std::endl;
    }
    else if constexpr(std::is_same_v< Container<int, int>, std::map<int, int> >)
    {
        std::cout << "std::map version" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    auto v = std::vector<double>{10, 20, 30};
    auto m = std::map<int, double>{ {10, 3.14}, {20, 2.7} };

    print_container(v);
    print_container(m);

    return 0;
}
