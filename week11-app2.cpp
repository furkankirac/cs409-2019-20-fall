// static polymorphism: Curiously Recurring Template Pattern (CRTP)
// SFINAE: Substitution Failure Is Not An Error

// return type resolver trick

#include <iostream>
#include <vector>

template<typename DERIVED>
struct Core
{
    void run()
    {
        // i need to tell the compiler to call a "solve" function
        ((DERIVED*)this)->solve();
    }
};

struct Solver_1 : public Core<Solver_1>
{
    void solve()
    {
        std::cout << "Solver 1\n";
    }

};

struct Solver_2 : public Core<Solver_2>
{
    void solve()
    {
        std::cout << "Solver 2\n";
    }

};

int main(int argc, char* argv[])
{
    auto s1 = Solver_1{};
    s1.run();

    auto s2 = Solver_2{};
    s2.run();

    return 0;
}
