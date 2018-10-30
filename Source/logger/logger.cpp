// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)
#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iterator>

#include "logger.hpp"


namespace logger
{

Logger::Logger(const std::string& input_file, const std::string& output_file)
: in_file(input_file)
, out_file(output_file, std::ios::app)
, _has_not_any_input_errors(in_file.is_open())
, _has_not_any_output_errors(out_file.is_open())
{
    if (has_any_errors())
    {
        repoort_error("Problem with initialization streams!");
    }
}

Logger::~Logger()
{
    in_file.close();
    out_file.close();
}

void Logger::repoort_error(const std::string_view message) const noexcept
{
    std::cerr << message << '\n'; // Report error.
    // 100 because no specification about length of the error message
    // but at MSDN talks about 94 characters.
    /*
    char sys_msg[100];
    std::cerr << "Error code: " << strerror_s(sys_msg, errno); // Get some info as to why.
    */
    // TODO(Vasiy): change this function because gcc does not support new C11 safe functions.
}

bool Logger::has_any_input_errors() const noexcept
{
    return !_has_not_any_input_errors;
}

bool Logger::has_any_output_errors() const noexcept
{
    return !_has_not_any_output_errors;
}

bool Logger::has_any_errors() const noexcept
{
    return !_has_not_any_input_errors && !_has_not_any_output_errors;
}

void Logger::restart_stream(const TypeStream io_stream)
{
    switch (io_stream)
    {
        case TypeStream::INPUT_STREAM:
            _has_not_any_input_errors = true;
            restart(in_file);
            break;

        case TypeStream::OUTPUT_STREAM:
            _has_not_any_output_errors = true;
            restart(out_file);
            break;

        default:
            assert(false);
            break;
    }
}

std::size_t Logger::count_lines_in_input_file()
{
    // New lines will be skipped unless we stop it from happening: 
    in_file.unsetf(std::ios_base::skipws);

    // Count the newlines with an algorithm specialized for counting:
    const std::size_t lineCount = std::count(std::istream_iterator<char>(in_file),
                                             std::istream_iterator<char>(), '\n') + 1;

    in_file.setf(std::ios_base::skipws);
    restart_stream(TypeStream::INPUT_STREAM);

    return lineCount;
}
} // namespace logger
