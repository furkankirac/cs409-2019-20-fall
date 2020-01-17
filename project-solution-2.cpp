#include <iostream>
#include <vector>
#include <utility>

/* Tiny Ranges Implementation by Furkan KIRAC
 * as part of CS409/509 - Advanced C++ Programming course in Ozyegin University
 * Supports transforming and filtering ranges and,
 * to<CONTAINER>() method for eagerly rendering the range into a CONTAINER.
 * Date: 20191222
 */

// predicates
namespace predicates
{
    auto less_than = [](auto threshold) { return [=](auto value) { return value < threshold; }; };
    auto greater_than = [](auto threshold) { return [=](auto value) { return value > threshold; }; };
    auto all_of = [](const auto ... preds) { return [=](auto value) { return (preds(value) && ...); }; };
}

namespace actions
{
    auto multiply_by = [](auto coef) { return [=](auto value) { return value * coef; }; };
    auto if_then = [](auto predicate, auto action) { return [=](auto value) { if(predicate(value)) value = action(value); return value; }; };
}

namespace views
{
    auto ints = [](int k=0) { return [k]() mutable { return k++; }; };
    auto odds = []() { return [k=1]() mutable { auto r = k; k += 2; return r; }; };
}

namespace algorithms
{
    // ---[ RANGE implementation
    template<typename Iterator>
    struct Range
    {
        using LazyIterator = Iterator; // required for accessing the used Iterator type from other locations
        Iterator m_begin;
        Iterator m_end;
        auto begin() const { return m_begin; }
        auto end() const { return m_end; }
    };

    template<typename Iterator>
    Range(Iterator, Iterator) -> Range<Iterator>;

    // ---[ TRANSFORM implementation
    template<typename Iterator, typename Callable>
    struct TransformingIterator : Iterator
    {
        using OriginalIterator = Iterator; // required for accessing the used Iterator type from other locations

        Callable callable;

        TransformingIterator(const Iterator iterator, const Callable& callable) : Iterator{iterator}, callable{callable} { }
        Iterator& get_orig_iter() { return ((Iterator&)*this); }
        double operator*() { return callable(*get_orig_iter()); }
    };

    auto transform = [](const auto action) {
        return [=](auto&& container) {
            using Container = std::decay_t<decltype(container)>;
            using Iterator = typename Container::iterator;
            using IteratorX = TransformingIterator<Iterator, decltype(action)>;
            return Range{IteratorX{container.begin(), action}, IteratorX{container.end(), action}};
        };
    };

    // ---[ FILTER implementation: implement your "Filtering Iterator" here
    template<typename Iterator, typename Callable>
    struct FilteringIterator : Iterator
    {
        using OriginalIterator = Iterator; // required for accessing the used Iterator type from other locations

        Iterator end;
        Callable callable;

        FilteringIterator(const Iterator iterator, const Iterator end, const Callable& callable)
            : Iterator{iterator}
            , end{end}
            , callable{callable}
        { }

        Iterator& get_orig_iter() { return ((Iterator&)*this); }

        void operator++() { ++get_orig_iter(); skip(); }
        void operator++(int) { get_orig_iter()++; skip(); }

        decltype(auto) operator*()
        {
            skip();
            auto& val = *get_orig_iter();
            return (val);
        }

        void skip()
        {
            while((Iterator&)*this != end && !callable(*get_orig_iter()))
                ++(*this);
        }
    };

    auto filter = [](const auto action) {
        return [=](auto&& container) {
            using Container = std::decay_t<decltype(container)>;
            using Iterator = typename Container::iterator;
            using IteratorX = FilteringIterator<Iterator, decltype(action)>;
            return Range{IteratorX{container.begin(), container.end(), action}, IteratorX{container.end(), container.end(), action}};
        };
    };

    // ---[ TO implementation: implement your "render into a container" method here
    template<template<typename...> typename ContainerBase>
    inline auto to()
    {
        return [](auto&& range) {
            using RangeType = std::decay_t<decltype(range)>;
            using LazyIterator = typename RangeType::LazyIterator;
            using OriginalIterator = typename LazyIterator::OriginalIterator;
            using T = std::remove_reference_t<decltype(*std::declval<OriginalIterator>())>;
            auto c = ContainerBase<T>{};
            for(const auto& x : range)
                c.push_back(x);
            return c;
        };
    }
}

template<typename CONTAINER, typename RANGE>
auto operator |(CONTAINER&& container, RANGE&& range) { return range(std::forward<CONTAINER>(container)); }

using namespace predicates;
using namespace actions;
using namespace algorithms;

int main(int argc, char* argv[])
{
    auto new_line = [] { std::cout << std::endl; };

    auto v = std::vector<double>{};
    auto odd_gen = views::odds();
    for(int i=0; i<5; ++i)
        v.push_back(odd_gen() * 2.5);
    // v contains {2.5, 7.5, 12.5, 17.5, 22.5} here

    auto range = v | transform(if_then(all_of(greater_than(2.0), less_than(15.0)), multiply_by(20)));
    for(auto a : range) // transformation is applied on the range as the for loop progresses
        std::cout << a << std::endl;
    // original v is not changed. prints {50.0, 150.0, 250.0, 17.5, 22.5}

    new_line();
    for(auto a : v | filter(greater_than(15))) // filter is applied lazily as the range is traversed
        std::cout << a << std::endl;
    // prints 17.5 and 22.5 to the console

    new_line();
    for(auto a : v | filter(less_than(15))) // filter is applied lazily as the range is traversed
        std::cout << a << std::endl;
    //  prints 2.5, 7.5 and 12.5

    new_line();
    auto u_transformed = std::vector<int>{10, 20, 30} | transform(multiply_by(2)) | to<std::vector>();
    for(auto a : u_transformed) // u_transformed is an std::vector<int> automatically because of to<std::vector>
        std::cout << a << std::endl;

    return 0;
}
