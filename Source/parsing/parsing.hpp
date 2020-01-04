// Copyright (C) 2019 Vasily Vasilyev (vasar007@yandex.ru)

#pragma once

#include <algorithm>
#include <cstring>
#include <deque>
#include <functional>
#include <string>
#include <utility>


// Forward declaration.
namespace vasily
{

struct RobotData;

enum class CoordinateSystem;

}

namespace utils
{

/**
 * \brief			           Parse input data and skips every 8 and 9 number.
 * \details                    Data contain one or more RobotData structure transfered into string.
 * \param[in] data	           Data for parsing.
 * \param[in] number_of_coords Number of coordinates in one structure.
 * \param[in] exclude_numbe    Number of exclude coordintes.
 * \return			           Deserialized data if parsed successful, empty container otherwise.
 */
[[nodiscard]]
std::string parse_full_data(const std::string& data, const int number_of_coords = 9,
                            const int exclude_number = 2);


/**
 * \brief          Parse input data to queue as messages.
 * \param[in] data Data for parsing.
 * \return         Deserialized data if parsed successful, empty container otherwise.
 */
[[nodiscard]]
std::deque<vasily::RobotData> parse_data(const std::string_view data);


/**
 * \brief          Check if input data are coordinate type or not.
 * \param[in] data Data for parsin.
 * \return         True if input data contains only one digit, false otherwise.
 */
std::pair<vasily::CoordinateSystem, bool> parse_coordinate_system(const std::string_view data);


/**
 * \brief            Split string by delimeter characters and don't include them.
 * \tparam Container Type of the contatiner for output.
 * \param[in] str    String to split.
 * \param[in] delims Delimiter characters (not STRINGS!).
 */
template <class Container>
Container	split(const std::string& str, const std::string_view delims = " ") noexcept;


/**
 * \brief            Split string by delimeter string and don't includes it.
 * \tparam Container Type of the contatiner for output.
 * \param[in] str    String to split.
 * \param[in] delim	 Delimiter string (not CHARACTERS!).
 */
template <class Container>
Container	fsplit(const std::string& str, const std::string_view delim = " ") noexcept;

#include "parsing.inl"

} // namespace utils
