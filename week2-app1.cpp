#include <iostream>

// Brief intro. to C++ basics. A comparative study with other languages.

// variables and functions and scope
//   primitive types
//   local, global, static variables
//   free, member, static functions
//   function return types

// auto
// OOP: struct, class, ctor/dtor, inheritance

// this ptr, static functions
// functions vs function parameters
// methods vs objects

// C++: a value semantics language. we work with THE VALUE. we can get references to the values as well.
// Java/Python/Javascript/...: reference semantics language. everything is a reference by default.

// OOP basics
// ctor/dtor
// copy-ctor, copy-assignment
// move-ctor, move-assignment
// inheritance

// function / operator overloading
// user-defined literals

// almost always auto - aaa rule: move type to the right
// unified/universal initialization

// namespaces
// dynamic polymorphism, v-table (default in Java, you opt-in in C++ with virtual keyword)

static float k;

auto b = true;

void foo()
{
    static auto initialized = false;
    if(!initialized)
    {
        std::cout << "initialized..." << std::endl;
        initialized = true;
    }
    b = 10;
}

//int k;
typedef float FLOAT;

//typedef struct
//{
//    int age;
//    float height;
//    char name[20];
//} Person;

struct Person
{
    static int num_persons;

    int age;
    float height;
    char* name;

    Person() // default-ctor
    {
        age = 0;
        height = 0.0f;
        name = new char[20];
        strcpy(name, "furkan");
        ++Person::num_persons;
    }

    ~Person()
    {
        delete[] name;
    }

    void print() // member function
    {
//        std::cout << "Age=" << this->age << std::endl;
        std::cout << "Age=" << age << std::endl;
    }
};

void printPerson(Person p) // free function
{
    std::cout << "Age=" << p.age << std::endl;
}


int main(int argc, char* argv[])
{
    auto i = 5.1;

    Person p1;
    Person p2;

    printPerson(p1);
//    p1.print();
//    printPerson(p2);
    p2.print();

    Person* p1_ptr = &p1;
    Person* p2_ptr = &p2;
    Person* p3_ptr;
    p3_ptr = p1_ptr;

    foo();
    foo();
    foo();
    foo();

    return 0;
}


int Person::num_persons = 0;



