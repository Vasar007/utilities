// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)

#ifndef PARSING_INL
#define PARSING_INL


template <class Container>
Container split(const std::string& str, const std::string_view delims) noexcept
{
    std::size_t previous = 0;
    std::size_t current = str.find_first_of(delims);
    if (current == std::string::npos)
    {
        return Container{};
    }

    // Maybe no need in such memory optimisation.
    std::size_t counter = 0;
    for (const auto& ch : delims)
    {
        counter += std::count(std::begin(str), std::end(str), ch);
    }

    Container cont;
    cont.reserve(counter + 1);
    while (current != std::string::npos)
    {
        cont.emplace_back(str.substr(previous, current - previous));
        previous = current + 1;
        current	= str.find_first_of(delims, previous);
    }

    cont.emplace_back(str.substr(previous, current - previous));

    return cont;
}

template <class Container>
Container fsplit(const std::string& str, const std::string_view delim) noexcept
{
    const std::size_t length = delim.size();
    std::size_t previous = 0;
    std::size_t current = str.find(delim);
    if (current == std::string::npos)
    {
        return Container{};
    }

    // Maybe no need in such memory optimisation.
    std::size_t counter = 0;
    const char* ptr_to_str = str.c_str();
    ptr_to_str = strstr(ptr_to_str, delim.data());
    while (ptr_to_str != nullptr)
    {
        ++counter;
        ++ptr_to_str;
        ptr_to_str = strstr(ptr_to_str, delim.data());
    }

    Container cont;
    cont.reserve(counter + 1);
    while (current != std::string::npos)
    {
        cont.emplace_back(str.substr(previous, current - previous));
        previous = current + length;
        current = str.find(delim, previous);
    }

    cont.emplace_back(str.substr(previous, current - previous));

    return cont;
}

#endif // PARSING_INL
