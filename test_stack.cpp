#include <iostream>

#include "containers/stack.hpp"

void	constructor(void)
{
	std::cout << "\n\n--- CONSTRUCTOR TESTS ---\n";
	ft::stack<int>	s;

	std::cout << "size: " << s.size() << "\n";
	s.push(42);
	std::cout << "size: " << s.size() << "\n";
	std::cout << "top: " << s.top() << "\n";
	s.push(24);
	std::cout << "size: " << s.size() << "\n";
	std::cout << "top: " << s.top() << "\n";
	return ;
}

int	main(void)
{
	constructor();
	return (0);
}