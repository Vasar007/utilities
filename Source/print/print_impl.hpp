// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>

#include "utility/valid_expression.hpp"


/*
 * \details Use cases:
 * \code
 * namespace NA
 * {
 *
 * class A
 * {
 * };
 *
 * std::string to_string(const A&)
 * {
 *   return { "to_string(A)" };
 * }
 *
 * } // namespace NA
 *
 * namespace NB
 * {
 *
 * class B
 * {
 * };
 *
 * std::ostream& operator<<(std::ostream& out, const B&)
 * {
 *   out << "oss(B)";
 *   return out;
 * }
 *
 * } // namespace NB
 *
 * namespace NC
 * {
 *
 * class C
 * {
 * public:
 *   friend std::ostream& operator<<(std::ostream& out, const C&)
 *   {
 *     out << "oss(C)";
 *     return out;
 *   }
 * };
 *
 * } // namespace NC
 *
 * namespace ND
 * {
 *
 * class D
 * {
 * public:
 *   std::string toString() const
 *   {
 *     return { "member::toString(D)" };
 *   }
 * };
 *
 * } // namespace ND
 *
 * utils::print(std::cout, "Some text\n");
 * utils::print(std::cout, 42);
 * utils::print(std::cout, NA::A());
 * utils::print(std::cout, NB::B());
 * utils::print(std::cout, NC::C());
 * utils::print(std::cout, ND::D());
 * \endcode
 */

namespace utils
{

// Expressions to test validity wrapped into tyedefs using decltype.
template <class T>
using Ostream = decltype(std::cout << std::declval<T>());
template <class T>
using StdFree = decltype(std::cout << std::to_string(std::declval<T>()));
template <class T>
using Free1 = decltype(std::cout << to_string(std::declval<T>()));
template <class T>
using Free2 = decltype(std::cout << toString(std::declval<T>()));
template <class T>
using Member1 = decltype(std::cout << std::declval<T>().to_string());
template <class T>
using Member2 = decltype(std::cout << std::declval<T>().toString());

////////////////////////////// The implementations. //////////////////////////////

template <class OutputStream, class T>
void _print_impl(OutputStream& out, const T& t, const std::string_view end_str = "")
{
    if constexpr (VALID_EXPRESSION<Ostream, T>)
    {
        out << t << end_str;
    }
    else if constexpr(VALID_EXPRESSION<StdFree, T>)
    {
        out << std::to_string(t) << end_str;
    }
    else if constexpr(VALID_EXPRESSION<Free1, T>)
    {
        out << to_string(t) << end_str;
    }
    else if constexpr(VALID_EXPRESSION<Free2, T>)
    {
        out << toString(t) << end_str;
    }
    else if constexpr(VALID_EXPRESSION<Member1, T>)
    {
        out << t.to_string() << end_str;
    }
    else if constexpr(VALID_EXPRESSION<Member2, T>)
    {
        out << t.toString() << end_str;
    }
    else
    {
        static_assert(templatize<T>(false), "T is not printable!");
    }
}

/**
 * \brief		        Print datatype to outstream.
 * \tparam OutputStream	Type of output stream.
 * \tparam T	        Datatype to print.
 * \param[out] out      Output stream to write.
 * \param[in] t         Data to print.
 */
template <class OutputStream, class T>
void print(OutputStream& out, const T& t)
{
    _print_impl(out, t, "");
}

/**
 * \brief			    Print datatypes (unlimited) to outstream.
 * \tparam OutputStream	Type of output stream.
 * \tparam T		    Datatype to print.
 * \tparam Args		    Variadic datatypes.
 * \param[out] out      Output stream to write.
 * \param[in] t		    Data to print.
 * \param[in] args	    Data to print.
 */
template <class OutputStream, class T, class... Args>
void print(OutputStream& out, const T& t, const Args&... args)
{
    _print_impl(out, t, " ");
    print(out, args...);
}

/**
 * \brief		        Print datatype to outstream.
 * \tparam OutputStream	Type of output stream.
 * \tparam T	        Datatype to print.
 * \param[out] out      Output stream to write.
 * \param[in] t         Data to print.
 */
template <class OutputStream, class T>
void println(OutputStream& out, const T& t)
{
    _print_impl(out, t, "\n");
}

/**
 * \brief			    FPrint datatypes (unlimited) to outstream.
 * \tparam OutputStream	Type of output stream.
 * \tparam T		    Datatype to print.
 * \tparam Args		    Variadic datatypes.
 * \param[out] out      Output stream to write.
 * \param[in] t		    Data to print.
 * \param[in] args	    Data to print.
 */
template <class OutputStream, class T, class... Args>
void println(OutputStream& out, const T& t, const Args&... args)
{
    _print_impl(out, t, " ");
    println(out, args...);
}

} // namespace utils

