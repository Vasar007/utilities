// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)
#include "printer.hpp"


namespace printer
{

Printer& Printer::get_instance() noexcept
{
    // Guaranteed to be destroyed. Instantiated on first use.
    static Printer instance{};
    return instance;
}

} // namespace printer
