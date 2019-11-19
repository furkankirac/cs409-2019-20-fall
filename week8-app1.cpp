// lambdas, stateful lambdas, lambda captures, mutable lambdas and equivalent classes
// if constexpr
// lvalue, rvalue
// TypeDisplayer trick
// std::move, perfect forwarding, std::forward

#include <iostream>

struct Lambda0
{
    int value = 0;

    auto operator() () {
//        static int value = 0;
        return value++;
    }
};


int main(int argc, char* argv[])
{
    auto i = 10.0f;
    decltype(i) j;

//    auto s1 = Lambda0{};
//    std::cout << s1() << std::endl;
//    std::cout << s1() << std::endl;

//    auto s2 = Lambda0{};
//    std::cout << s2() << std::endl;
//    std::cout << s2() << std::endl;

    auto l1 = [value = 0]() mutable {
        return value++;
    };
    std::cout << l1() << std::endl;
    std::cout << l1() << std::endl;

    auto l2 = [value = 0]() mutable {
        return value++;
    };
    std::cout << l2() << std::endl;
    std::cout << l2() << std::endl;

    return 0;
}
