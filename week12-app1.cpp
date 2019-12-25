#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

// static_cast, dynamic_cast, const_cast, reinterpret_cast
// exceptions, noexcept

// advanced corner cases:
// - lifecycle extension of returned instances

// - compile-time array size deduction, and std::size

// - decltype(auto)

// - std::invoke_result

// - template template parameters

// - std::declval: simulation of instance creations in unevaluated contextes.
// i.e., find data type pointed by an iterator, first by a function template, then by a class template

struct A
{
    virtual void run() { }
};

struct B : A
{
    void run() override { }
};

int main(int argc, char* argv[])
{
    auto a = 10;

    auto d1 = (double)a; // c-style cast
    auto d2 = static_cast<double>(a);

    B* Bptr = new B();
    A* Aptr = static_cast<A*>(Bptr);

    // if Aptr is really an instance of B (checked at run-time)
    // returned pointer is a B*
    // else nullptr is returned
    // kind of "instance of" in Java
    B* Bptr2 = dynamic_cast<B*>(Aptr);

    Aptr->run();





    return 0;
}
