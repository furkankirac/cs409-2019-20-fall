// union
// std::variant

#include <iostream>
#include <variant>
#include <map>

union Foo
{
    int i;
    float f;
};

enum FooType { integer, floating };

struct Bar
{
    Foo value;
    FooType type;

    Bar(int i) { value.i = i; type = integer; }
    Bar(float f) { value.f = f; type = floating; }
};

using Joker = std::variant<int, float, double, const char*>;


int main(int argc, char* argv[])
{
    auto bar1 = Bar{10};
    auto bar2 = Bar{3.14f};

    if(bar1.type == integer)
        std::cout << bar1.value.i << std::endl;
    else if(bar1.type == floating)
        std::cout << bar1.value.f << std::endl;

    auto j = Joker{};
    j = 5;
    j = 5.3;
    j = "Hi there";

    std::visit([](auto v) {
        using T = decltype(v);
        if constexpr(std::is_same_v<T, int>)
        {
            std::cout << "int\n";
        }
        else if constexpr(std::is_same<T, float>::value)
        {
            std::cout << "float\n";
        }
        else
        {
            std::cout << "other\n";
        }
    }, j);


//    auto m = std::map<Joker, Joker>{};
//    m[5] = "Hello";
//    m["Hi there"] = 3.14f;

//    for(const auto& [key, value] : m)
//    {
//    }


    return 0;
}
