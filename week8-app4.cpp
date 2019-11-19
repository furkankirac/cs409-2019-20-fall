// std::move, perfect forwarding, std::forward
// TypeDisplayer trick
// if constexpr

#include <iostream>
#include <vector>

template<typename T>
inline T&& move(const T& t)
{
   return (T&&)t;
}

struct Foo
{
    std::vector<int> v;

    Foo() : v{} { std::cout << "Default c-tor." << std::endl; }

    Foo(const Foo& other) : v{other.v} { std::cout << "Copy c-tor." << std::endl; }
    Foo(Foo&& other) : v{(std::vector<int>&&)other.v} { std::cout << "Move c-tor." << std::endl; }
};


Foo get_foo()
{
    auto f = Foo{};
    return f;
//    return std::move(f); // don't distrupt return value optimization with std::move
}

int main(int argc, char* argv[])
{
//    auto foo = Foo{}; // default c-tor of Foo
//    auto foo1 = foo; // copy c-tor of Foo
//    auto foo2 = std::move(foo); // copy c-tor of Foo

    auto foo = get_foo();

    return 0;
}
