#include <iostream>
#include <cassert>

#include "algorithm/algorithm.hpp"
#include "containers/vector.hpp"

void	equal_test(void)
{
	std::cout << "\n\n--- EQUAL TESTS ---\n";
	ft::vector<int>	v(1, 100);
	ft::vector<int>	v2(v);
	ft::vector<int>	v3(3, 300);
	ft::vector<int>	v4(v3);

	v4[2] = 200;
	std::cout << std::boolalpha;
	assert(ft::equal(v.begin(), v.end(), v2.begin()) == true);
	assert(ft::equal(v.begin(), v.end(), v3.begin()) == false);
	assert(ft::equal(v3.begin(), v3.end(), v4.begin()) == false);
	v4 = v3;
	assert(ft::equal(v3.begin(), v3.end(), v4.begin()) == true);
	std::cout << "\n\nEQUAL TESTS: OK\n\n";
	return ;
}

void	lexicographical_test(void)
{
	std::cout << "\n\n--- LEXICOGRAPHICAL TESTS ---\n";
	ft::vector<std::string>	v(2, "hola");
	ft::vector<std::string>	v2(2, "hola");
	ft::vector<int>			i(2, 20);
	ft::vector<int>			i2(2, 20);

	assert(ft::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end()) == false);
	v2.back() = "adios";
	assert(ft::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end()) == false);
	v.back() = "adios";
	v2.back() = "aloha";
	assert(ft::lexicographical_compare(v.begin(), v.end(), v2.begin(), v2.end()) == true);
	assert(ft::lexicographical_compare(i.begin(), i.end(), i2.begin(), i2.end()) == false);
	i2.back() = 10;
	assert(ft::lexicographical_compare(i.begin(), i.end(), i2.begin(), i2.end()) == false);
	i.back() = 1;
	assert(ft::lexicographical_compare(i.begin(), i.end(), i2.begin(), i2.end()) == true);
	std::cout << "\n\nLEXICOGRAPHICAL TESTS: OK\n\n";
	return ;
}

int	main(void)
{
	equal_test();
	lexicographical_test();
	return (0);
}