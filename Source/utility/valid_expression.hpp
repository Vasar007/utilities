// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)
#ifndef VALID_EXPRESSION_HPP
#define VALID_EXPRESSION_HPP

#include <type_traits>


namespace utils
{

// Not-so-important helpers.
namespace detail
{

    template <template <typename...> typename E, typename C, typename... T>
    struct Valid_Expression_T : public std::false_type
    {
    };

    template <template <typename...> typename E, typename... T>
    struct Valid_Expression_T<E, std::void_t<E<T...> >, T...> : public std::true_type
    {
    };

} // namespace detail

template <typename T, typename O>
constexpr decltype(auto) templatize(O&& value) noexcept
{
    return std::forward<O>(value);
}

// The final templated boolean.
template <template <typename...> typename Expr, typename... Args>
constexpr auto VALID_EXPRESSION = detail::Valid_Expression_T<Expr, void, Args...>::value;

} // namespace utils

#endif // VALID_EXPRESSION_HPP
