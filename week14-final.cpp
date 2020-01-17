#include <iostream>

auto TUPLE = [](auto ... inputs) { return [=](auto accessor) { return accessor(inputs...); }; };

auto head_to_tuple = [](auto first, auto ... rest) { return TUPLE(first); };
auto HEAD = [](const auto& tuple) { return tuple(head_to_tuple); };

auto tail_to_tuple = [](auto first, auto ... rest) { return TUPLE(rest...); };
auto TAIL = [](const auto& tuple) { return tuple(tail_to_tuple); };

// Q1's answer will be inserted here
auto HEAD_REST = [](const auto& tuple) { return std::pair{HEAD(tuple), TAIL(tuple)}; };

// Q2's answer will be inserted here. Obey the supplied code template below.
auto printer = [](auto ... all) { ((std::cout << all << std::endl), ...); };
auto PRINT = [](const auto& tuple) { tuple(printer); };

// Q3's answer to be inserted here.
template<typename First, typename ... Rest>
void reverse_printer(First first, Rest ... rest)
{
    if constexpr(sizeof...(rest) > 0)
        reverse_printer(rest...);
    std::cout << first << std::endl;
}
//
auto reverser = [](auto ... all) { reverse_printer(all...); };
auto PRINT_REVERSE = [](const auto& tuple) { tuple(reverser); };

// Q4a's answer to be inserted here.
template<typename T> struct is_char_ptr                 { static constexpr auto value = false; };
template<>           struct is_char_ptr<char*>          { static constexpr auto value = true; };
template<>           struct is_char_ptr<const char*>    { static constexpr auto value = true; };

// Q4b's answer to be inserted here.
template<typename T>
constexpr auto is_char_ptr_v = is_char_ptr<T>::value;

// Q5a's answer to be inserted here.
template<typename T>
auto arithmetic_value_of(const T& value)
{
    if constexpr(!is_char_ptr_v<T>)
        return value;
    else
        return 0;
}

// Q5b's answer to be inserted here. Only for CS409 students.
auto summer = [](auto ... all) { return (arithmetic_value_of(all) + ...); };
auto SUM = [](const auto& tuple) { return tuple(summer); };

// Q5b's answer to be inserted here. Only for CS509 students.
auto averager = [](auto ... all) { return (arithmetic_value_of(all) + ...) / (double)((arithmetic_value_of(all)!=0) + ...); };
auto AVERAGE = [](const auto& tuple) { return tuple(averager); };


int main(int argc, char* argv[])
{
    auto tuple = TUPLE(9, 3.14f, 5.0, "Hi!");

    auto [head, rest] = HEAD_REST(tuple);
    std::cout << "Head is:" << std::endl;
    PRINT(head);
    std::cout << "Rest is:" << std::endl;
    PRINT(rest);

    std::cout << "Reversed tuple is:" << std::endl;
    PRINT_REVERSE(tuple);

    std::cout << "Sum of arithmetic values in tuple = " << SUM(tuple) << std::endl;
    std::cout << "Average of arithmetic values != 0 in tuple = " << AVERAGE(tuple) << std::endl;

    return 0;
}
