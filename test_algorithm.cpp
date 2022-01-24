#include <iostream>

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
	std::cout << "\nv(1, 100) equal v2(1, 100)? ";
	std::cout << ft::equal(v.begin(), v.end(), v2.begin()) << "\n";
	std::cout << "\nv(1, 100) equal v3(3, 300)? ";
	std::cout << ft::equal(v.begin(), v.end(), v3.begin()) << "\n";
	std::cout << "\nv3(3, 300) equal v4={300, 300, 200}? ";
	std::cout << ft::equal(v3.begin(), v3.end(), v4.begin()) << "\n";
	v4 = v3;
	std::cout << "\nv3(3, 300) equal v4(3, 300)? ";
	std::cout << ft::equal(v3.begin(), v3.end(), v4.begin()) << "\n";
	return ;
}

void	lexicographical_test(void)
{
	std::cout << "\n\n--- LEXICOGRAPHICAL TESTS ---\n";
	ft::vector<std::string>	v(2, "hola");
	ft::vector<std::string>	v2(2, "hola");
	ft::vector<int>			i(2, 20);
	ft::vector<int>			i2(2, 20);

	std::cout << "\nv(2, \"hola\") and v2(2, \"hola\") ";
	std::cout << ft::lexicographical_compare(v.begin(), v.end(),
	v2.begin(), v2.end()) << "\n";
	v2.back() = "adios";
	std::cout << "\nv={\"hola\", \"hola\"} and v2={\"hola\", \"adios\"} ";
	std::cout << ft::lexicographical_compare(v.begin(), v.end(),
	v2.begin(), v2.end()) << "\n";
	v.back() = "adios";
	v2.back() = "aloha";
	std::cout << "\nv={\"hola\", \"adios\"} and v2={\"hola\", \"aloha\"} ";
	std::cout << ft::lexicographical_compare(v.begin(), v.end(),
	v2.begin(), v2.end()) << "\n";
	std::cout << "\ni(2, 20) and i2(2, 20) ";
	std::cout << ft::lexicographical_compare(i.begin(), i.end(),
	i2.begin(), i2.end()) << "\n";
	i2.back() = 10;
	std::cout << "\ni(2, 20) and i2={20, 10} ";
	std::cout << ft::lexicographical_compare(i.begin(), i.end(),
	i2.begin(), i2.end()) << "\n";
	i.back() = 1;
	std::cout << "\ni{20, 1} and i2={20, 10} ";
	std::cout << ft::lexicographical_compare(i.begin(), i.end(),
	i2.begin(), i2.end()) << "\n";
	return ;
}

int	main(void)
{
	equal_test();
	lexicographical_test();
	return (0);
}