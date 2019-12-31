#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

template<typename Key, typename Value>
struct Pair
{
    Key key;
    Value value;

    Pair() = default;
    Pair(const Key& key, const Value& value) : key{key}, value{value} { }

    template<int times>
    void print() const
    {
        for(auto i=0; i<times; ++i)
            std::cout << "Key = " << key << ", Value = " << value << std::endl;
    }
};
//void print(const Pair* p) const
//{
//    std::cout << "Key = " << p->key << ", Value = " << p->value << std::endl;
//}

// inheriting from a template class
template<typename First, typename Second, typename Third>
struct Triple : public Pair<First, Second>
{
    Third detail;
    Triple() : Pair<First, Second>{}, detail{} { }
//    Triple() : key{}, value{}, detail{} { }
    Triple(const First& key, const Second& value, const Third& detail)
        : Pair<First, Second>{key, value}
        , detail{detail}
    { }

    void print() const
    {
        // since base class is a template class you need to use this->
        // since called method is a template method you need to assist compiler
        //  by writing "template " after ->
        // otherwise angle brackets < > can be mistreated as
        // less than < and greater than > signs! (corner cases are available)
        static_cast<const Pair<First, Second>*>(this)->template print<1>();
        std::cout << "Detail = " << detail << std::endl;
    }
};


int main(int argc, char* argv[])
{
    auto int_float = Pair<int, float>{10, 3.14f};
    int_float.print<10>();

    auto triple = Triple<int, float, const char*>{10, 3.14f, "Hi there!"};
    triple.print();

    return 0;
}
