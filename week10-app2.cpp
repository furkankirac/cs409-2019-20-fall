// overloaded{}

// union
// std::variant

#include <iostream>

struct Callable1 { auto operator() (int) const { std::cout << "int\n"; } };
struct Callable2 { auto operator() (float) const { std::cout << "float\n"; } };
struct Callable3 { auto operator() (double) const { std::cout << "double\n"; } };

struct Callable : Callable1, Callable2, Callable3
{
    using Callable1::operator (), Callable2::operator (), Callable3::operator ();
};


template<typename ... Ts>
struct overloaded : Ts...
{
    using Ts::operator ()...;
};


template<typename ... Ts>
overloaded(Ts ...) -> overloaded<Ts...>;


auto callable = overloaded{
        [](int) { std::cout << "int\n"; },
        [](float) { std::cout << "float\n"; },
        [](double) { std::cout << "double\n"; },
        [](auto) { std::cout << "other\n"; },
        };


int main(int argc, char* argv[])
{
    auto c = Callable{};
    c(int{});
    c(float{});

    callable(int{});
    callable(float{});
    callable(double{});
    callable("");

    return 0;
}
