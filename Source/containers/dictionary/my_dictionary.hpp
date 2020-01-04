/*
Необходимо реализовать класс контейнера, реализующий интерфейс Dictionary и способный выбросить
исключение, реализующее интерфейс NotFoundException.
При разработке допускается использовать STL. Кроме этого, внутренняя реализация ничем не ограничена.

template<class TKey, class TValue>
class Dictionary
{
public:
	virtual ~Dictionary() = default;

	virtual const TValue& Get(const TKey& key) const = 0;
	virtual void Set(const TKey& key, const TValue& value) = 0;
	virtual bool IsSet(const TKey& key) const = 0;
};

template<class TKey>
class NotFoundException : public std::exception
{
public:
	virtual const TKey& GetKey() const noexcept = 0;
};
*/

#pragma once

#include <exception>
#include <shared_mutex>
#include <unordered_map>

#include "dictionary.hpp"

namespace vv
{

template <class TKey, class TValue>
class MyDictionary final : public Dictionary<TKey, TValue>
{
public:
	MyDictionary() = default;
	
	MyDictionary(const MyDictionary&) = delete;
	
	MyDictionary(MyDictionary&&) = delete;
	
	MyDictionary& operator=(const MyDictionary&) = delete;
	
	MyDictionary& operator=(MyDictionary&&) = delete;
	
	~MyDictionary() override = default;

	const TValue& Get(const TKey& key) const override;

	void Set(const TKey& key, const TValue& value) override;

	bool IsSet(const TKey& key) const override;

private:
	std::unordered_map<TKey, TValue> _data;

	mutable std::shared_mutex _mutex;
};

} // namespace vv

#include "my_dictionary.inl"
