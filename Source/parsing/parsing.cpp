// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#include <algorithm>
#include <iterator>
#include <sstream>
#include <vector>
#include <utility>

#include "data_structure/data_structure.hpp"
#include "utility/utility.hpp"

#include "parsing.hpp"


namespace utils
{

[[nodiscard]]
std::string parse_full_data(const std::string& data, const int number_of_coords,
                            const int exclude_number)
{
    if (number_of_coords <= exclude_number || data.empty())
    {
        return {};
    }

    auto str_storage = utils::split<std::vector<std::string>>(data);

    str_storage.erase(std::remove(std::begin(str_storage), std::end(str_storage), ""), std::end(str_storage));

    if (str_storage.size() % number_of_coords != 0)
    {
        return {};
    }

    std::string result;
    int count = 0;
    for (const auto& str : str_storage)
    {
        if (!utils::is_correct_number(str))
        {
            result.clear();
            break;
        }

        bool flag = true;
        for (int i = 0; i < exclude_number; ++i)
        {
            if (count % number_of_coords == number_of_coords - i - 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            result += str + " ";
        }

        ++count;
    }

    return result;
}

std::deque<vasily::RobotData> parse_data(const std::string_view data)
{
    std::deque<vasily::RobotData> result;

    std::stringstream raw_data(data.data());
    vasily::RobotData robot_data{};
    while (raw_data >> robot_data)
    {
        if (!raw_data.fail())
        {
            result.emplace_back(robot_data);
        }
    }
    return result;
}

std::pair<vasily::CoordinateSystem, bool> parseCoordinateSystem(const std::string_view data)
{
    const bool parsed_result = data.size() == 1 && utils::is_correct_number(data);

    if (!parsed_result)
    {
        return { vasily::CoordinateSystem::INVALID, parsed_result };
    }

    if (const int type = utils::string_to_int(data); 0 <= type && type <= 2)
    {
        return { static_cast<vasily::CoordinateSystem>(type), parsed_result };
    }

    return { vasily::CoordinateSystem::INVALID, parsed_result };
}

} // namespace utils
