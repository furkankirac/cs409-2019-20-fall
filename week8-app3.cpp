// lvalue, rvalue
// TypeDisplayer trick
// std::move, perfect forwarding, std::forward
// if constexpr

#include <iostream>
#include <vector>

struct Big
{
    //...
};

struct Huge
{
    std::vector<Big> v;
    // ...
};

auto foo1(int& i, float& f)
{
    return Huge{};
//    return i + f;

}
auto foo2(const int& i, const float& f) { return i + f; }
auto foo3(int&& i, float&& f) {
    i++;
    return i + f;
}

int main(int argc, char* argv[])
{
    auto k = 3;
    auto p1 = 10;
    auto p2 = 100.0f;
    auto huge = foo1(p1, p2); //RVO = return value optimization
//    std::cout << foo1(p1, p2) << std::endl;

    std::cout << foo2(10, 100.0f) << std::endl;

    std::cout << foo3(10, 100.0f) << std::endl;
    return 0;
}
