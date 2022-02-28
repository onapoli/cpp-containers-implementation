#include <cassert>
#include <iostream>

#include "containers/map.hpp"

void	construction(void)
{
	ft::map<int, int>			m;
	ft::map<int, int>::iterator	it;

	m.insert(ft::pair<int, int>(10, 10));
	it = m.begin();
	assert((*it).first == 10);
	assert((*it).second == 10);
	std::cout << "\nCONSTRUCTION TESTS: OK\n";
	return ;
}

void	add_sub(void)
{
	ft::map<int, int>			m;
	ft::map<int, int>::iterator	it;
	int							counter;

	m.insert(ft::pair<int, int>(10, 10));
	m.insert(ft::pair<int, int>(20, 20));
	m.insert(ft::pair<int, int>(30, 30));
	counter = 10;
	for (it = m.begin(); it != m.end(); ++it)
	{
		assert((*it).first == counter);
		counter += 10;
	}
	std::cout << "\nADDITION SUBSTRACTION TESTS: OK\n";
	return ;
}

void	comparison(void)
{
	ft::map<int, int>			m;
	ft::map<int, int>::iterator	it;
	ft::map<int, int>::iterator	it2;
	int							counter;

	m.insert(ft::pair<int, int>(10, 10));
	m.insert(ft::pair<int, int>(20, 20));
	m.insert(ft::pair<int, int>(30, 30));
	counter = 0;
	it = m.begin();
	while (it++ != m.end())
		++counter;
	assert(counter == 3);
	it2 = m.end();
	//end_offset OF it IS 2 BECAUSE OF while LOOP INCREMENT it++
	assert(it != it2);
	--it;
	assert(it == it2);
	--it;
	--it2;
	assert(it == it2);
	assert((*it).first == 30);
	assert((*it2).first == 30);
	std::cout << "\nCOMPARISON TESTS: OK\n";
	return ;
}

int	main(void)
{
	construction();
	add_sub();
	comparison();
	std::cout << std::endl;
	return (0);
}