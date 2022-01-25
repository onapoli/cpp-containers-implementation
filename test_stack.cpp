#include <iostream>
#include <cassert>
#include <deque>

#include "containers/stack.hpp"

void	constructor(void)
{
	std::cout << "\n\n--- CONSTRUCTOR TESTS ---\n";
	ft::stack<int>						s;
	ft::stack< int, std::deque<int> >	s2;
	std::deque<int>						d(2, 200);
	ft::stack<int, std::deque<int> >	s3(d);
	ft::vector<std::string>				v(3, "hola");
	ft::stack<std::string>				s4(v);

	std::cout << std::boolalpha;
	std::cout << "\nSTART FROM EMPTY DEFAULT CONTAINER\n";
	std::cout << "s.size(): " << s.size() << "\n";
	assert(s.size() == 0);
	s.push(42);
	std::cout << "s.size(): " << s.size() << "\n";
	std::cout << "s.top(): " << s.top() << "\n";
	assert(s.size() == 1 && s.top() == 42);
	s.push(24);
	std::cout << "s.size(): " << s.size() << "\n";
	std::cout << "s.top(): " << s.top() << "\n";
	assert(s.size() == 2 && s.top() == 24);
	std::cout << "\nWORKS WITH ANY COMPATIBLE CONTAINER TYPES LIKE deque\n";
	std::cout << "s2.empty(): " << s2.empty() << "\n";
	assert(s2.empty() == true);
	s2.push(42);
	std::cout << "s2.size(): " << s2.size() << "\n";
	std::cout << "s2.top(): " << s2.top() << "\n";
	assert(s2.size() == 1 && s2.top() == 42);
	std::cout << "\nUNDERLYING CONTAINER IS A COPY\n";
	d.pop_back();
	std::cout << "s3.size(): " << s3.size() << "\n";
	assert(s3.size() == 2);
	std::cout << "\nDEFAULT CONTAINER TYPE IS vector\n";
	std::cout << "s4.size(): " << s4.size() << std::endl;
	assert(s4.size() == 3);
	return ;
}

void	top_push_pop(void)
{
	std::cout << "\n\n--- TOP PUSH POP TESTS ---\n";
	ft::stack<int>	s;

	std::cout << "\nPUSH TO EMPTY stack\n";
	s.push(1);
	s.push(2);
	std::cout << "s.size(): " << s.size() << "\n";
	std::cout << "s.top(): " << s.top() << "\n";
	assert(s.size() == 2 && s.top() == 2);
	std::cout << "\nPOP UNTIL EMPTY\n";
	s.pop();
	s.pop();
	std::cout << "s.size(): " << s.size() << "\n";
	std::cout << "s.empty(): " << s.empty() << "\n";
	assert(s.size() == 0 && s.empty() == true);
	std::cout << "\nPOP FROM EMPTY stack\n";
	s.pop();
	std::cout << "s.size(): " << s.size() << "\n";
	std::cout << "s.empty(): " << s.empty() << "\n";
	assert(s.size() == 0 && s.empty() == true);
	return ;
}

int	main(void)
{
	constructor();
	top_push_pop();
	return (0);
}