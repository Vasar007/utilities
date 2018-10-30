// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)
#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <mutex>
#include <string>

#include "utility/utility.hpp"


/**
 * \brief Additional namespace to work with logging.
 */
namespace logger
{
    
/**
 * \brief Class used to write data to output file.
 */
class Logger
{
public:
    /**
     * \brief Set of type of streams.
     */
    enum class TypeStream
    {
        INPUT_STREAM,
        OUTPUT_STREAM
    };

    /**
     * \brief Input file stream.
     */
    std::ifstream in_file; // ORDER DEPENDENCY => 1.

    /**
     * \brief Output file stream.
     */
    std::ofstream out_file; // ORDER DEPENDENCY => 2.


    /**
     * \brief                 Constructor.
     * \param[in] input_file  File name for input. 
     * \param[in] output_file File name for output.
     */
    explicit Logger(const std::string& input_file, const std::string& output_file);

    /**
     * \brief Destructor.
     */
    ~Logger();

    /**
     * \brief           Default copy constructor.
     * \param[in] other Other object.
     */
    Logger(const Logger& other) = delete;

    /**
     * \brief           Default copy assignment operator.
     * \param[in] other Other object.
     * \return          Return copied object.
     */
    Logger& operator=(const Logger& other) = delete;

    /**
     * \brief            Default move constructor.
     * \param[out] other Other object.
     */
    Logger(Logger&& other) = delete;

    /**
     * \brief            Default move assignment operator.
     * \param[out] other Other object.
     * \return           Return moved object.
     */
    Logger& operator=(Logger&& other) = delete;

    /**
     * \brief          Write (unlimited) data in output stream.
     * \tparam Args    Variadic data types.
     * \param[in] args Data to write.
     */
    template <typename... Args>
    void write(const Args&... args);

    /**
     * \brief          Write (unlimited) data in output stream and new line character.
     * \tparam Args    Variadic data types.
     * \param[in] args Data to write.
     */
    template <typename... Args >
    void writeln(const Args&... args);

    /**
     * \brief    Read data from input stream. Read data until space character (' ').
     * \tparam T Type of input data.
     * \return   Readed data.
     */
    template <typename T>
    T read();

    /**
     * \brief    Read data from input stream. Read data until newline character ('\n').
     * \tparam T Type of input data.
     * \return   Readed data.
     */
    template <typename T>
    T readln();

    /**
     * \brief  Show if any errors in input stream occurred.
     * \return Flag that contains answer.
     */
    bool has_any_input_errors() const noexcept;

    /**
     * \brief  Show if any errors in output stream occurred.
     * \return Flag that contains answer.
     */
    bool has_any_output_errors() const noexcept;

    /**
     * \brief  Show if any errors in input and output streams occurred.
     * \return Flag that contains answer.
     */
    bool has_any_errors() const noexcept;

    /**
     * \brief               Restart file stream.
     * \param[in] io_stream Type of stream to restart.
     */
    void restart_stream(const TypeStream io_stream);

    /**
     * \brief  Count lines in input file.
     * \return Number of lines.
     */
    std::size_t count_lines_in_input_file();


private:
    /**
     * \brief Flag used to show if any errors in input stream occured.
     */
    bool        _has_not_any_input_errors; // ORDER DEPENDENCY => 3.    
    /**
     * \brief Flag used to show if any errors in ouput stream occured.
     */
    bool        _has_not_any_output_errors; // ORDER DEPENDENCY => 4.

    /**
     * \brief Mutex to lock thread for safety.
     */
    std::mutex  _mutex;


    /**
     * \brief             Restart current stream.
     * \tparam Stream     Type of stream to restart.
     * \param[out] stream Stream to restart.
     */
    template <typename Stream>
    void restart(Stream& stream);

    /**
     * \brief       Write data in output stream.
     * \tparam T    Type of output data.
     * \param[in] t Data to write.
     */
    template <typename T>
    void write_impl(const T& t);

    /**
     * \brief          Write (unlimited) data in output stream.
     * \tparam T       Type of output data.
     * \tparam Args    Variadic data types.
     * \param[in] t    Data to write.
     * \param[in] args Data to write.
     */
    template <typename T, typename... Args>
    void write_impl(const T& t, const Args&... args);

    /**
     * \brief       Write data in output stream and new line character.
     * \tparam T    Type of output data.
     * \param[in] t Data to write.
     */
    template <typename T>
    void writeln_impl(const T& t);

    /**
     * \brief          Write (unlimited) data in output stream and new line character.
     * \tparam T       Type of output data.
     * \tparam Args    Variadic data types.
     * \param[in] t    Data to write.
     * \param[in] args Data to write.
     */
    template <typename T, typename... Args>
    void writeln_impl(const T& t, const Args&... args);

    /**
     * \brief             Report error if any error occurred with streams.
     * \param[in] message Print this string to user with error.
     */
    void repoort_error(const std::string_view message) const noexcept;
};

#include "logger.inl"

} // namespace logger

#endif // LOGGER_H
