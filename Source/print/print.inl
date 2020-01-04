// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#pragma once


template <class T>
constexpr std::string_view type_name() noexcept
{
// Macros used to work on every platform.
#ifdef __clang__
    std::string_view p = __PRETTY_FUNCTION__;
    return std::string_view(p.data() + 33, p.size() - 33 - 1);
#elif defined(__GNUC__)
    std::string_view p = __PRETTY_FUNCTION__;
    #if __cplusplus < 201402
        return std::string_view(p.data() + 36, p.size() - 36 - 1);
    #else
        return std::string_view(p.data() + 48, p.find(';', 49) - 48);
    #endif
#elif defined(_MSC_VER)
    std::string_view p = __FUNCSIG__;
    return std::string_view(p.data() + 83, p.size() - 84 - 6);
#endif
}

template <class OutputStream, class Container>
void print_container(OutputStream& out, const Container& container)
{
    std::copy(std::begin(container), std::end(container),
              std::ostream_iterator<typename Container::value_type>(out, " "));
}

template <class OutputStream, class Container>
void println_container(OutputStream& out, const Container& container)
{
    std::copy(std::begin(container), std::end(container),
              std::ostream_iterator<typename Container::value_type>(out, " "));
    std::cout << '\n';
}
