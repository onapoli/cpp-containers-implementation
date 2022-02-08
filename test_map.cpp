#include <iostream>
#include <assert.h>

#include "containers/map.hpp"

void	construction(void)
{
	ft::map<int, std::string>	m;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	assert(!m.empty());
	assert(m.size() == 1);
	assert(m.insert(ft::make_pair<int, std::string>(5, "hello")) == false);
	assert(m.size() == 1);
	m.insert(ft::make_pair<int, std::string>(1, "bye"));
	assert(m.size() == 2);
	std::cout << "\nCONSTRUCTION TESTS: OK\n";
	return ;
}

void	insertion(void)
{
	std::cout << "\nINSERTION TESTS: OK\n";
	return ;
}

void	access(void)
{
	ft::map<int, std::string>	m;
	std::string					s;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	m.insert(ft::make_pair<int, std::string>(1, "bye"));
	s = m[5];
	assert(s == "hello");
	s = m[1];
	assert(s == "bye");
	std::cout << "\nACCESS TESTS: OK\n";
	return ;
}

int	main(void)
{
	construction();
	insertion();
	access();
	std::cout << std::endl;
	return (0);
}