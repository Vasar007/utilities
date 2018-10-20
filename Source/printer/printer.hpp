#ifndef PRINTER_H
#define PRINTER_H

#include <mutex>

#include "print/print.hpp"


/**
 * \brief Additional namespace to work with printing to output streams.
 */
namespace printer
{

/**
 * \brief Additional namespace which contains subclass to output.
 */
namespace item
{

    /**
     * \brief               Subclass used to output data in constructor.
     * \tparam OutputStream Type of output stream.
     * \tparam T            Datatype to print (need to be overloaded operator '<<').
     */
    template <class OutputStream, class T>
    struct ItemPrinter
    {
        /**
         * \brief          Outputting constructor.
         * \param[out] out Output stream to write.
         * \param[in] t    Data to print.
         */
        ItemPrinter(OutputStream& out, const T& t)
        {
            out << t << ' ';
        }
    };

} // namespace item

/**
 * \brief Singleton used to deterministic write data to output stream.
 */
class Printer
{
public:
    /**
     * \brief  Get the instance of singleton.
     * \return Reference to singleton object.
     */
    static Printer& getInstance() noexcept;

    /**
     * \brief Default destructor.
     */
    ~Printer() = default;

    /**
     * \brief			Default copy constructor.
     * \param[in] other Other object.
     */
    Printer(const Printer& other) = delete;

    /**
     * \brief			Default copy assignment operator.
     * \param[in] other Other object.
     * \return			Return copied object.
     */
    Printer& operator=(const Printer& other) = delete;

    /**
     * \brief			 Default move constructor.
     * \param[out] other Other object.
     */
    Printer(Printer&& other) = delete;

    /**
     * \brief			 Default move assignment operator.
     * \param[out] other Other object.
     * \return			 Return moved object.
     */
    Printer& operator=(Printer&& other) = delete;

    /**
     * \brief               Overloaded operator to print data to outstream with subclasses.
     * \tparam OutputStream Type of output stream.
     * \tparam Args         Variadic datatypes (need to be overloaded operator '<<').
     * \param[out] out      Output stream to write..
     * \param[in] args      Data to print.
     */
    template<class OutputStream, class... Args>
    void operator()(OutputStream& out, const Args&... args);

    /**
     * \brief               Print datatypes (unlimited) to outstream.
     * \tparam OutputStream Type of output stream.
     * \tparam Args         Variadic datatypes (need to be overloaded operator '<<').
     * \param[out] out      Output stream to write..
     * \param[in] args      Data to print.
     */
    template<class OutputStream, class... Args>
    void write(OutputStream& out, const Args&... args);

    /**
     * \brief               Print datatypes (unlimited) to outstream and new line character.
     * \tparam OutputStream Type of output stream.
     * \tparam Args         Variadic datatypes (need to be overloaded operator '<<').
     * \param out           Output stream to write..
     * \param args          Data to print.
     */
    template<class OutputStream, class... Args>
    void writeLine(OutputStream& out, const Args&... args);


private:
    /**
     * \brief Mutex to lock thread for safety.
     */
    std::mutex _mutex;


    /**
     * \brief Default constructor.
     */
    Printer() = default;
};

#include "printer.inl"

} // namespace printer

#endif // PRINTER_H
