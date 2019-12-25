#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <type_traits>

// advanced corner cases:
// - std::declval: simulation of instance creations in unevaluated contextes.
// i.e., find data type pointed by an iterator, first by a function template, then by a class template

template<typename ...> struct TD;

template<typename Iterator>
void get_iterator_type(const Iterator& iterator)
{
//    TD<remove_reference_t<decltype(*iterator)>> a;
}

template<typename Iterator>
struct iterator_type
{
//    using type = std::remove_reference_t<decltype(*Iterator{})>;
    using type = std::remove_reference_t<decltype(*std::declval<Iterator>())>;
};


int main(int argc, char* argv[])
{
    auto v = std::vector<float>{10.1f, 20.5f, 30.8f};
    for(auto it = v.begin(); it != v.end(); ++it)
        std::cout << *it << std::endl;

    for(const auto& a : v)
        std::cout << a << std::endl;

    for(const auto& a : {10.1, 20.2, 30.3})
        std::cout << a << std::endl;

//    get_iterator_type(v.begin());
    using T = iterator_type<std::vector<float>::iterator>::type;
//    TD<T> a;

    return 0;
}
