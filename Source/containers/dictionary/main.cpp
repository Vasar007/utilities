#include <iostream>

#include "key_not_found_exception.hpp"
#include "my_dictionary.hpp"


int main()
{
	try
	{
		vv::MyDictionary<int, std::string> dict;
		dict.Set(0, "value 0");
		dict.Set(1, "2");
		dict.Set(2, "2");
		dict.Set(2, "3");
		std::cout << std::boolalpha << dict.IsSet(0) << ' ' << dict.Get(0) << '\n';
		std::cout << std::boolalpha << dict.IsSet(1) << ' ' << dict.Get(1) << '\n';
		std::cout << std::boolalpha << dict.IsSet(2) << ' ' << dict.Get(2) << '\n';
	}
	catch (const vv::KeyNotFoundException<int>& ex)
	{
		std::cerr << ex.what() << '\n';
		std::cerr << ex.GetKey() << '\n';
	}
}
