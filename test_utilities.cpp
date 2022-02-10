#include <iostream>
#include <cassert>

#include "utility/utility.hpp"

void	pair_test(void)
{
	ft::pair<int, int>						pr;
	ft::pair<int, std::string>				pr2;
	ft::pair<int, std::string>::first_type	i;
	ft::pair<int, std::string>::second_type	s;

	pr = ft::make_pair<int, int>(1, 2);
	i = 42;
	s = "Cuarenta y dos";
	std::cout << "pr.first: " << pr.first << " pr.second: ";
	std::cout << pr.second << "\n";
	assert(pr.first == 1 && pr.second == 2);
	pr2 = ft::make_pair<int, std::string>(i, s);
	std::cout << "pr2.first: " << pr2.first << " pr2.second: ";
	std::cout << pr2.second << "\n";
	assert(pr2.first == 42 && pr2.second == "Cuarenta y dos");
	return ;
}

int	main(void)
{
	pair_test();
	return (0);
}
