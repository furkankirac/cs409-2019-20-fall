#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

// advanced corner cases:
// - decltype(auto)

// - std::invoke_result

// - template template parameters

// - std::declval: simulation of instance creations in unevaluated contextes.
// i.e., find data type pointed by an iterator, first by a function template, then by a class template

int get_int_byval() { return 5; }
int& get_int_byref() { static auto a = 5; return a; }

template<typename...> struct TypeDisplayer;

struct Func
{
    template<typename Callable>
    auto operator() (Callable callable) const
    {
        // gets the return type at compile type
//        using ret_t = std::invoke_result_t<Callable>;
//        TypeDisplayer<ret_t> a;
        return callable();
    }
};
int main(int argc, char* argv[])
{
    auto func1 = Func{};

    auto func2 = [](auto callable) -> decltype(auto) {
        return callable();
    };

    decltype(auto) i1 = get_int_byval();
    decltype(auto) i2 = get_int_byref();

    decltype(auto) j1 = func1(&get_int_byval);
    decltype(auto) j2 = func1(&get_int_byref);

    decltype(auto) k1 = func2(&get_int_byval);
    decltype(auto) k2 = func2(&get_int_byref);
//    TypeDisplayer<decltype(i1), decltype(i2)> a;

    return 0;
}
