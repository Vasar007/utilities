// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)

#ifndef LOGGER_INL
#define LOGGER_INL


template <class Stream>
void Logger::restart(Stream& stream)
{
    if constexpr (std::is_same<Stream, std::ifstream>::value)
    {
        stream.clear();
        stream.seekg(0, std::ios::beg);
    }
    else if constexpr (std::is_same<Stream, std::ofstream>::value)
    {
        stream.clear();
        stream.seekp(0, std::ios::beg);
    }
    else
    {
        stream.clear();
    }
}

template <class T>
void Logger::write_impl(const T& t)
{
    // It is necessary to flush buffer here.
    out_file << t << ' ' << std::flush;
    _has_not_any_output_errors = !out_file.fail();
}

template <class T, class... Args>
void Logger::write_impl(const T& t, const Args&... args)
{
    out_file << t << ' ';
    _has_not_any_output_errors = !out_file.fail();

    write_impl(args...);
}

template <class T>
void Logger::writeln_impl(const T& t)
{
    // std::endl because it is necessary to flush buffer here.
    out_file << t << std::endl;
    _has_not_any_output_errors = !out_file.fail();
}

template <class T, class... Args>
void Logger::writeln_impl(const T& t, const Args&... args)
{
    out_file << t << ' ';
    _has_not_any_output_errors = !out_file.fail();

    writeln_impl(args...);
}

template <class... Args>
void Logger::write(const Args&... args)
{
    std::lock_guard lock_guard(_mutex);
    if (out_file)
    {
        write_impl(args...);
    }
    else
    {
        repoort_error("Data could not be written to file!");
    }
}

template <class... Args>
void Logger::writeln(const Args&... args)
{
    std::lock_guard lock_guard(_mutex);
    if (out_file)
    {
        writeln_impl(args...);
    }
    else
    {
        repoort_error("Data could not be written to file!");
    }
}

template <class T>
T Logger::read()
{
    std::string readed_data;
    if (in_file)
    {
        in_file >> readed_data;
    }
    else
    {
        repoort_error("File could not be opened!");
    }

    bool flag;
    T t = utils::from_string<T>(readed_data, flag);

    _has_not_any_input_errors = !in_file.fail() && flag;

    return t;
}

template <class T>
T Logger::readln()
{  
    std::string readed_data;
    if (in_file)
    {
        std::getline(in_file, readed_data);
    }
    else
    {
        repoort_error("File could not be opened!");
    }

    bool flag;
    T t = utils::from_string<T>(readed_data, flag);

    _has_not_any_input_errors = !in_file.fail() && flag;

    return t;
}

#endif // LOGGER_INL
