// return type resolver trick

#include <iostream>

struct Proxy
{
    template<typename T>
    operator T()
    {
        if constexpr(std::is_same_v<T, int>)
            return 5;
        else if constexpr(std::is_same_v<T, float>)
            return 5.3f;
    }
};

inline auto foo() { return Proxy{}; }

int main(int argc, char* argv[])
{
    int i = foo();
    std::cout << i << std::endl;

    float f = foo();
    std::cout << f << std::endl;

    return 0;
}
