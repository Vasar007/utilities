#pragma once

#include <iterator>
#include <mutex>

#include "key_not_found_exception.hpp"


namespace vv
{

template <class TKey, class TValue>
const TValue& MyDictionary<TKey, TValue>::Get(const TKey& key) const
{
	std::shared_lock lock(_mutex);

	const auto search = _data.find(key);
	if (search == std::end(_data))
	{
		throw KeyNotFoundException(key);
	}
	return search->second;
}

template <class TKey, class TValue>
void MyDictionary<TKey, TValue>::Set(const TKey& key, const TValue& value)
{
	std::unique_lock lock(_mutex);

	const auto search = _data.find(key);
	if (search == std::end(_data))
	{
		_data.emplace(key, value);
	}
	else
	{
		search->second = value;
	}
}

template <class TKey, class TValue>
bool MyDictionary<TKey, TValue>::IsSet(const TKey& key) const
{
	std::shared_lock lock(_mutex);

	const auto search = _data.find(key);
	return search != std::end(_data);
}

} // namespace vv
