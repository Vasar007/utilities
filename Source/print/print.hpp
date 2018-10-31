// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)

#ifndef PRINT_H
#define PRINT_H

#include <iostream>
#include <iterator>
#include <type_traits>
#include <typeinfo>
#include <string>
#include <string_view>


#ifndef _MSC_VER
    #include <cxxabi.h>
#endif

#include "print_impl.hpp"


namespace utils
{

/**
 * \brief         Print string to standart outstream.
 * \param[in] str String to print.
 */
void std_output(const std::string_view str) noexcept;


/**
 * \brief         Fast print string to outstream.
 * \param[in] str String to print.
 */
void fast_output(const std::string& str) noexcept;


/**
 * \brief    Define the type name of variable.
 * \tparam T Datatype to process (use 'decltype()' to send data).
 * \return   String which contains type name of variable.
 */
template <class T>
constexpr std::string_view type_name() noexcept;


template <class OutputStream, class Container>
void print_container(OutputStream& out, const Container& container);


template <class OutputStream, class Container>
void println_container(OutputStream& out, const Container& container);


void pause(const std::string_view message = "\nPress the Enter key to continue...");


void pause_clear(const std::string_view message = "Press ENTER to continue...");

#include "print.inl"

} // namespace utils

#endif // PRINT_H
