// perfect forwarding, std::forward
// TypeDisplayer trick
// if constexpr

#include <iostream>
#include <vector>
#include <string>

template<typename ...>
struct TypeDisplayer;

template<typename ... Ts>
auto bar(Ts&& ... ts)
{
    auto z = TypeDisplayer<Ts...>{};
    ((std::cout << ts << std::endl), ...);
}

template<typename ... Ts>
inline auto foo(Ts&& ... ts)
{
//    bar(ts...);
    bar(std::forward<Ts>(ts)...);
}

struct Big
{
    std::string longstring;
    Big() {}
    Big(const std::string& s) : longstring{s} { }

    Big(const Big& other) : longstring{other.longstring} { }
    Big(Big&& other) : longstring{std::move(other.longstring)} { }
};

int main(int argc, char* argv[])
{
    auto v = std::vector<int>{10, 20, 30, 40}; // 4 integers, each of them are 10,20,30,40 respectively
    std::cout << v[0] << std::endl;
    std::cout << v[1] << std::endl;

    auto v2 = std::vector<int>(10); // 10 integers all of the default constructed.

    auto v3 = std::vector<Big>{};
    v3.push_back(std::move(Big{"HelloHelloHelloHelloHelloHelloHelloHelloHelloHello"}));

    v3.emplace_back("HelloHelloHelloHelloHelloHelloHelloHelloHelloHello");

//    auto k = 50;
//    foo("Hi", 5, k);

    return 0;
}
