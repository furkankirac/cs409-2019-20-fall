// dynamic polymorphism: virtual functions, v-table, virtual inheritance
// static polymorphism: Curiously Recurring Template Pattern
// SFINAE: Substitution Failure Is Not An Error

// return type resolver trick

#include <iostream>
#include <vector>

struct Animal
{
    virtual void eat() { std::cout << "I am ANIMAL!\n"; } // (1)
    virtual void jump() { };
};

struct Predator : virtual Animal
{
    virtual void kill() { }
};

struct Mammal : virtual Animal
{
    void eat() override { std::cout << "I ate (mammal).\n"; } // (2)
};

struct Wolf : Mammal, Predator
{
    void eat() override { std::cout << "Mmm, delicious.\n"; } // (3)
    void kill() override { }
};

struct Bird : Mammal
{
    void eat() override { std::cout << "I am a bird\n"; } // (4)
};

int main(int argc, char* argv[])
{
    Animal* a1_ptr = new Animal();
    Animal* a2_ptr = new Mammal();

//    a1_ptr->eat();
//    a2_ptr->eat();

    auto v = std::vector<Animal*>{a1_ptr, a2_ptr};
    for(auto p : v)
        p->eat();



//    auto a = Animal{};
//    a.eat(); // calls (1)

//    auto m = Mammal{};
//    m.eat(); // calls (2)

//    auto w = Wolf{};
//    w.eat(); // calls (3)

//    auto b = Bird{};
//    b.eat(); // calls (4)

//    auto v = std::vector<Animal>{a, m, w, b};

    return 0;
}
