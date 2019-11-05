// one type of functional programming example in C++: template specializations

constexpr int factorial_compiletime(int n)
{
    if(n <= 1)
        return 1;
    return n*factorial_compiletime(n-1);
}

//template<int n> struct Factorial    { static const int value = n * Factorial<n-1>::value; };
//template<>      struct Factorial<1> { static const int value = 1; };
//template<>      struct Factorial<0> { static const int value = 1; };

template<int n> inline int factorial()     { return n*factorial<n-1>(); }
template<>      inline int factorial<1>()  { return 1; }
template<>      inline int factorial<0>()  { return 1; }

//struct Factorial_4 { static const int value = 4 * Factorial_3::value; };
//struct Factorial_5 { static const int value = 5 * Factorial_4::value; };

int main(int argc, char* argv[])
{
//    return Factorial<5>::value;
//    return factorial<5>();
    return factorial_compiletime(5);
}
