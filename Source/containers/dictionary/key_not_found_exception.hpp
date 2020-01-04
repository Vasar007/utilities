#pragma once

#include <utility>

#include "not_found_exception.hpp"


namespace vv
{

template <class TKey>
class KeyNotFoundException final : public NotFoundException<TKey>
{
public:
	explicit KeyNotFoundException(TKey key)
	: _key(std::move(key))
	{
	}

	const TKey& GetKey() const noexcept override
	{
		return _key;
	}

	const char* what() const noexcept override
	{
		return "Key was not found in dictionary.";
	}

private:
	TKey _key;
};

} // namespace vv
