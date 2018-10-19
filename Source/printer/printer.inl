#ifndef PRINTER_INL
#define PRINTER_INL


template<class OutputStream, class... Args>
void Printer::operator()(OutputStream& out, const Args&... args)
{
    std::lock_guard lockGuard(_mutex);
    (item::ItemPrinter(out, args), ...);
}

template<class OutputStream, class... Args>
void Printer::write(OutputStream& out, const Args&... args)
{
    std::lock_guard lockGuard(_mutex);
    utils::print(out, args...);
}

template<class OutputStream, class... Args>
void Printer::writeLine(OutputStream& out, const Args&... args)
{
    std::lock_guard lockGuard(_mutex);
    utils::println(out, args...);
}

#endif // PRINTER_INL
