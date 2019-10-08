#include <iostream>

// function / operator overloading

// OOP:
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment
// inheritance

// user-defined literals

// almost always auto - aaa rule: move type to the right
// unified/universal initialization

// namespaces
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword)

float get_pi()
{
    return 3.14152f;
}


float get_pi(int precision)
{
    if(precision == 1)
        return 3.1f;
    if(precision == 2)
        return 3.14f;

    return 3.1415;
}

struct Int
{
    int value;
    /*explicit */Int(int value) : value(value) { }

    operator int()
    {
        return value;
    }
};


bool operator<(Int i, int j)
{
    return i.value < j;
}


Int operator "" _myint(unsigned long long value)
{
    return Int(value);
}

//struct COUT { };
//COUT operator <<(COUT, const char*);
//COUT operator <<(COUT, int);
//COUT operator <<(COUT, float);
//...

int main(int argc, char* argv[])
{
    Int i1 = 5;
    auto i3 = 5_myint;

    auto i1_casted = (int)i1;

    int i2 = 10;

    auto f = (float)i2;

//    if(i1.value < i2)
//        std::cout << "Oley" << std::endl;
    if(i1 < i2)
        std::cout << "Oley" << i1 <<  std::endl;

    auto pi1 = get_pi();
    auto pi2 = get_pi(2);
    return 0;
}
