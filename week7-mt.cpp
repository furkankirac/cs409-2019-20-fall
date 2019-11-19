#include <iostream>

template<typename T> struct is_integer_v        { static const auto value = false; };
template<>           struct is_integer_v<int>   { static const auto value = true; };

template<typename T>
inline void print_int_only(const T& val)
{
    if(is_integer_v<T>::value) // “if constexpr” is better, but doesn’t matter here
        std::cout << val << std::endl;
}

template<typename ... Ts>
inline void print_ints_only(const Ts& ... ts)
{
    (print_int_only(ts), ...);
}

template<typename STYLER, typename T>
inline void print_int_only_with_style(STYLER styler, const T& val)
{
    if constexpr(is_integer_v<T>::value)
        styler(val);
}

template<typename STYLER, typename ... Ts>
inline void print_ints_only_with_style(STYLER styler, const Ts& ... ts)
{
    (print_int_only_with_style(styler, ts), ...);
}

template<typename STYLER>
inline void operator >>(int val, STYLER styler)
{
    styler(val);
}

struct Styler
{
    int value;
    Styler(int value) : value{value} { }
    void operator()() const { std::cout << '[' << value << ']' << std::endl; }
};

int main(int argc, char* argv[])
{    
    print_ints_only(1, "needs to hi", 5, "others"); // prints 1\n5\n
    auto styler = [](int v) { std::cout << '[' << v << ']' << std::endl; };
    print_ints_only_with_style(styler, 1, "needs to hi", 5, "others"); // prints [1]\n[5]\n

    // shall call styler with 100 and print [100]\n
    100 >> styler;

    auto k = Styler{100};
    k(); // prints [100]\n

    return 0;
}
