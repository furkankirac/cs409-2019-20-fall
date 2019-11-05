// variadic parameters: parameter packs and pack expansions

#include <iostream>

template<typename T>
inline void PRINT(const T& t)
{
    std::cout << "'" << t << "'" << std::endl;
}

template<typename ... Ts>
inline void print(const Ts& ... ts)
{
    (PRINT(ts), ...);
}

int main(int argc, char* argv[])
{
//    print<int>(5);
//    print<int, const char*, double, float>(5, "Hello", 5.3, 3.14f);
    print(5, "Hello", 5.3, 3.14f);

//    std::cout << 5 << std::endl;
//    std::cout << "Hello" << std::endl;
//    std::cout << 5.3 << std::endl;
//    std::cout << 3.14f << std::endl;

    return 0;
}
