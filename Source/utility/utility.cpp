// Copyright (C) 2018 Vasily Vasilyev (vasar007@yandex.ru)

#include <cassert>
#include <chrono>
#include <ctime>
#include <random>

#include "print/print.hpp"
#include "utility.hpp"


namespace utils
{

namespace
{

    std::default_random_engine create_random_engine()
    {
        const auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }
    
    auto RANDOM_ENGINE = create_random_engine();

} // anonymous namespace

[[nodiscard]]
int random_int(const int exclusive_border)
{
    if (exclusive_border == 0)
    {
        return 0;
    }
    if (exclusive_border < 0)
    {
        std::uniform_int_distribution<int> distr(exclusive_border + 1, 0);
        return distr(RANDOM_ENGINE);
    }

    std::uniform_int_distribution<int> distr(0, exclusive_border - 1);
    return distr(RANDOM_ENGINE);
}

bool is_correct_number(const std::string_view str, const int flag)
{
    char* ptr;
    if (const double out = strtod(str.data(), &ptr); flag == 1)
    {
        utils::println(std::cout, '\n', out);
    }
    return *ptr == 0;
}

[[nodiscard]]
int string_to_int(const std::string_view str)
{
    if (utils::is_correct_number(str))
    {
        return std::atoi(str.data());
    }

    return 0;
}

std::string get_current_system_time() noexcept
{
    /*
    // Get current time.
    const auto time_now = std::chrono::system_clock::now();

    // Convert time to ctime.
    std::time_t time_now_t = std::chrono::system_clock::to_time_t(time_now);

    // Parse time in readable format.
    std::tm time_info{};
    localtime_s(&time_info, &time_now_t);

    // The string result produced by asctime_s contains exactly 26 characters and
    // has the form => Wed Jan 02 02:03:55 1980\n\0.
    constexpr std::size_t kSize = 26;
    char timebuf[kSize];

    if (const errno_t err = asctime_s(timebuf, kSize, &time_info); err != 0)
    {
        std::cout << "Error code: " << err << '\n';
        return { "" };
    }

    return timebuf;
    */
    // TODO(Vasily): change this function because gcc does not support new C11 safe functions.
    return { "getCurrentSystemTime() does not support" };
}

bool almost_equal_2_complements(float a, float b, const int max_ulps)
{
    // max_ulps must not be negative and not too large to NaN was not equal to any number.
    assert(max_ulps > 0 && max_ulps < 4 * 1024 * 1024);

    int aInt = *DOUBLE_STATIC_CAST(int*, a);
    // Remove sign in aInt, if you have to get the correct ordered sequence.
    if (aInt < 0)
    {
        // aInt &= 0x7fffffff;
        aInt = 0x80000000 - aInt;
    }

    // Similarly for bInt.
    int bInt = *DOUBLE_STATIC_CAST(int*, b);
    if (bInt < 0)
    {
        // bInt &= 0x7fffffff;
        bInt = 0x80000000 - bInt;
    }

    const int intDiff = std::abs(aInt - bInt);

    return intDiff <= max_ulps;
}

} // namespace utils
