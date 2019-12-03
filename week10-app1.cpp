// class template type deductions
// deduction guides
// function object overloads
// generic lambdas
// overloaded{}

// union
// std::variant

#include <iostream>

template<typename T1, typename T2>
struct Pair
{
    T1 first;
    T2 second;
};

template<typename T1, typename T2>
Pair(T1, T2) -> Pair<T1, T2>;


struct Callable
{
    auto operator() (int) const { std::cout << "int\n"; }
    auto operator() (float) const { std::cout << "float\n"; }
};

template<typename T1, typename T2>  struct is_same          { static const auto value = false; };
template<typename U>                struct is_same<U, U>    { static const auto value = true; };

template<typename T1, typename T2>
constexpr auto is_same_v = is_same<T1, T2>::value;

struct CallableX
{
    template<typename T>
    auto operator() (T) const
    {
        if constexpr(is_same_v<T, int>)
        {
            std::cout << "int\n";
        }
        else if constexpr(is_same<T, float>::value)
        {
            std::cout << "float\n";
        }
    }
};

auto callablex = [](auto t) {
    using T = decltype(t);
    if constexpr(is_same_v<T, int>)
    {
        std::cout << "int\n";
    }
    else if constexpr(is_same<T, float>::value)
    {
        std::cout << "float\n";
    }
};


int main(int argc, char* argv[])
{
    auto p1 = Pair{10.0, 20};

    auto c = Callable{};
    c(int{});
    c(float{});

    auto cx = CallableX{};
    cx(int{});
    cx(float{});

    callablex(int{});
    callablex(float{});

//    int a = 10;

//    switch(a)
//    {
//    case 5: // ...
//    case 10: // ...
//        break;
//    default:
//        break;

//    }

    return 0;
}
