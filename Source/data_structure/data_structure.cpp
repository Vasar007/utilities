// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#include <algorithm>
#include <cmath>
#include <iterator>
#include <sstream>
#include <string>

#include "data_structure.hpp"


namespace vasily
{

std::string RobotData::to_string() const
{
    std::stringstream string_stream{};

    std::copy(std::begin(coordinates), std::end(coordinates), 
              std::ostream_iterator<int>(string_stream, " "));

    std::copy(std::begin(parameters), std::end(parameters),
              std::ostream_iterator<int>(string_stream, " "));
    
    return string_stream.str();
}

double RobotData::length() const
{
    double result = 0.0;
    for (std::size_t i = 0; i < NUMBER_OF_COORDINATES; ++i)
    {
        result += 1.0 * coordinates.at(i) * coordinates.at(i) / (TRANSFER_NUMBER * TRANSFER_NUMBER);
    }
    return std::sqrt(result);
}

std::istream& operator>>(std::istream& in, RobotData& robot_data)
{
    for (auto& coordinate : robot_data.coordinates)
    {
        in >> coordinate;
    }

    for (auto& parameter : robot_data.parameters)
    {
        in >> parameter;
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const RobotData& robot_data)
{
    std::copy(std::begin(robot_data.coordinates), std::end(robot_data.coordinates),
              std::ostream_iterator<int>(out, " "));

    std::copy(std::begin(robot_data.parameters), std::end(robot_data.parameters),
              std::ostream_iterator<int>(out, " "));

    return out;
}

std::wostream& operator<<(std::wostream& out, const RobotData& robot_data)
{
    std::copy(std::begin(robot_data.coordinates), std::end(robot_data.coordinates),
              std::ostream_iterator<int, wchar_t>(out, L" "));

    std::copy(std::begin(robot_data.parameters), std::end(robot_data.parameters),
              std::ostream_iterator<int, wchar_t>(out, L" "));

    return out;
}

} // namespace vasily
