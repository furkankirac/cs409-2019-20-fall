// if constexpr, std::is_integral_v<T>

// forwarding reference
// TypeDisplayer trick
// reference collapsing rules

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

template<typename T>    struct is_integral         { static const bool value = false; };
template<>              struct is_integral<char>   { static const bool value = true; };
template<>              struct is_integral<short>  { static const bool value = true; };
template<>              struct is_integral<int>    { static const bool value = true; };
template<>              struct is_integral<long>   { static const bool value = true; };

template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;

template<typename ...>
struct TypeDisplayer;

template<typename T>
void foo(T&& value) // forwarding reference
{
//    auto a = TypeDisplayer<T>{};

    if constexpr(is_integral_v<T>)
    {
        std::cout << "An integral type T has been given. Great.";
    }
    else
    {
        std::cout << "Bored...";
    }
}


int main(int argc, char* argv[])
{
    int k = 5;
    foo(k);

    return 0;
}
