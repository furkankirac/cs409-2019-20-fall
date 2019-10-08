#include <iostream>

// const, east/west const, const correctness
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


int main(int argc, char* argv[])
{
//    float const pi = 3.1415f; // east const
    const float pi = 3.1415f; // west const
    float e = 2.7f;

    float const * ptr = &pi;
//    const float* ptr = &pi;
    ptr = &e;

    float const * const ptr2 = &pi;
//    const float * const ptr2 = &pi;
//    *ptr = 3.0f; // read-only variable is not assignable
//    ptr2 = &e; // error, ptr2 is read-only







    return 0;
}
