// variadic parameters: parameter packs and pack expansions

template<int a, int b> struct Div       { static const int value = a/b; };
template<int k       > struct Div<k, 0> { static const int value = k; };

template<int a, int b> struct Mul { static const int value = a*b; };

// fold expression
//template<int ... As> struct Multiply
//{
//    static const int value = (As * ...);
//};

// fold expression with initial value (first)
template<int first, int ... rest> struct Multiply
{
    static const int value = (first * ... * rest);
};


//struct Multiply_5_10_2
//{
//    static const int value = (5 * 10 * 2);
//};

int main(int argc, char* argv[])
{
    return Multiply<5, 10, 2>::value;
//    return Mul< Mul<5, 10>::value, 2 >::value;
}
