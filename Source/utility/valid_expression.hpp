// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#pragma once

#include <type_traits>


namespace utils
{

// Not-so-important helpers.
namespace detail
{

    template <template <class...> class E, class C, class... T>
    struct Valid_Expression_T : public std::false_type
    {
    };

    template <template <class...> class E, class... T>
    struct Valid_Expression_T<E, std::void_t<E<T...> >, T...> : public std::true_type
    {
    };

} // namespace detail

template <class T, class O>
constexpr decltype(auto) templatize(O&& value) noexcept
{
    return std::forward<O>(value);
}

// The final templated boolean.
template <template <class...> class Expr, class... Args>
constexpr auto VALID_EXPRESSION = detail::Valid_Expression_T<Expr, void, Args...>::value;

} // namespace utils
