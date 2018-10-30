// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)

#ifndef PRINTER_INL
#define PRINTER_INL


template<typename OutputStream, typename... Args>
void Printer::operator()(OutputStream& out, const Args&... args)
{
    std::lock_guard lock_guard(_mutex);
    (item::ItemPrinter(out, args), ...);
}

template<typename OutputStream, typename... Args>
void Printer::write(OutputStream& out, const Args&... args)
{
    std::lock_guard lock_guard(_mutex);
    utils::print(out, args...);
}

template<typename OutputStream, typename... Args>
void Printer::writeln(OutputStream& out, const Args&... args)
{
    std::lock_guard lock_guard(_mutex);
    utils::println(out, args...);
}

#endif // PRINTER_INL
