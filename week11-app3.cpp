// SFINAE: Substitution Failure Is Not An Error

// return type resolver trick

#include <iostream>
#include <vector>

template<bool b, typename T> struct enable_if          { };
template<typename T>         struct enable_if<true, T> { using type = T; };



//template<typename T, typename enable_if<std::is_integral_v<T>, int>::type = 0>
//inline void print(const T& t)
//{
//    std::cout << t << std::endl;
//}

template<typename T>
inline
typename enable_if<std::is_integral_v<T>, void>::type
print(const T& t)
{
    std::cout << t << std::endl;
}

template<typename T>
inline
typename enable_if<!std::is_integral_v<T>, void>::type
print(const T& t)
{
    std::cout << "[" << t << "]" << std::endl;
}

int main(int argc, char* argv[])
{
    // enable_if<true, int>::type ----> int
    // enable_if<false, int>::type ----> error

    print(3);
    print(3.5);
    print(3.5f);
    print("Hello");

    return 0;
}
