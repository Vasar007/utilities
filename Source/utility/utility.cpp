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

    std::default_random_engine createRandomEngine()
    {
        const auto seed = static_cast<unsigned long>(std::time(nullptr));
        return std::default_random_engine(seed);
    }
    
    auto RANDOM_ENGINE = createRandomEngine();

} // anonymous namespace

[[nodiscard]]
int randomInt(const int exclusiveBorder)
{
    if (exclusiveBorder == 0)
    {
        return 0;
    }
    if (exclusiveBorder < 0)
    {
        std::uniform_int_distribution<int> distr(exclusiveBorder + 1, 0);
        return distr(RANDOM_ENGINE);
    }

    std::uniform_int_distribution<int> distr(0, exclusiveBorder - 1);
    return distr(RANDOM_ENGINE);
}

bool isCorrectNumber(const std::string_view str, const int flag)
{
    char* ptr;

    const double out = strtod(str.data(), &ptr);

    if (flag == 1)
    {
        utils::println(std::cout, '\n', out);
    }

    return *ptr == 0;
}

[[nodiscard]]
int stringToInt(const std::string_view str)
{
    if (utils::isCorrectNumber(str))
    {
        return std::atoi(str.data());
    }

    return 0;
}

std::string getCurrentSystemTime() noexcept
{
    /*
    // Get current time.
    const auto timeNow = std::chrono::system_clock::now();

    // Convert time to ctime.
    std::time_t timeNowT = std::chrono::system_clock::to_time_t(timeNow);

    // Parse time in readable format.
    std::tm timeInfo{};
    localtime_s(&timeInfo, &timeNowT);

    // The string result produced by asctime_s contains exactly 26 characters and
    // has the form => Wed Jan 02 02:03:55 1980\n\0.
    constexpr std::size_t kSize = 26;
    char timebuf[kSize];
    const errno_t err = asctime_s(timebuf, kSize, &timeInfo);

    if (err != 0)
    {
        std::cout << "Error code: " << err << '\n';
        return { "" };
    }

    return timebuf;
    */
    // TODO(Vasily): change this function because gcc does not support new C11 safe functions.
    return { "getCurrentSystemTime() does not support" };
}

bool almostEqual2Complement(float a, float b, const int maxUlps)
{
    // maxUlps must not be negative and not too large to NaN was not equal to any number.
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);

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

    return intDiff <= maxUlps;
}

} // namespace utils
