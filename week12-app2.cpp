#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

// advanced corner cases:
// - compile-time array size deduction, and std::size

// - decltype(auto)

// - std::invoke_result

// - template template parameters

// - std::declval: simulation of instance creations in unevaluated contextes.
// i.e., find data type pointed by an iterator, first by a function template, then by a class template

std::string foo()
{
    auto s = std::string{"Hi there"};
    return s;
}

int array[] = { 10, 20, 30 };
//char str[] = "Hello";
char str[] = { 'H', 'e', 'l', 'l', 'o', 0};
//std::array<int, 3> array{ 10, 20, 30};

template<typename T, size_t sz>
constexpr size_t array_size(T(&)[sz]) { return sz; }

float array2[array_size(array)];

int main(int argc, char* argv[])
{
    const auto& s = foo(); // life cycle extended

    std::cout << array_size(str) << std::endl;
    std::cout << std::size(str) << std::endl;

    return 0;
}
