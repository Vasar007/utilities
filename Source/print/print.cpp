// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#include <limits>

#include "print.hpp"


namespace utils
{

void std_output(const std::string_view str) noexcept
{
    std::cout << str;
}

void fast_output(const std::string& str) noexcept
{
    if (const int returnValue = std::puts(str.c_str()); returnValue == EOF)
    {
        // POSIX requires that errno is set.
        std::perror("puts() failed.");
    }
}

void pause(const std::string_view message)
{
    do
    {
        std::cout << message;
    }
    while (std::cin.get() != '\n');
}


void pause_clear(const std::string_view message)
{
    std::cout << message << std::flush;
    std::cin.seekg(0u, std::ios::end);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

} // namespace utils
