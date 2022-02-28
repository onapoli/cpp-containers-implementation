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
	ft::map<int, int>	m;
	/*
	**	Pensar cómo comprobar con las funciones públicas de map
	**	que un árbol es correcto.
	**
	**	IDEAS
	**
	**	1. Recorrerlo en orden y comprobar que el orden es correcto.
	**	2. Comprobar key de extremos (first y last iterator)
	*/
	m.insert(ft::make_pair<int, int>(10, 10));
	m.insert(ft::make_pair<int, int>(20, 20));
	m.insert(ft::make_pair<int, int>(30, 30));
	m.insert(ft::make_pair<int, int>(40, 40));
	m.printTree();
	m.insert(ft::make_pair<int, int>(50, 50));
	m.printTree();
	m.insert(ft::make_pair<int, int>(60, 60));
	m.insert(ft::make_pair<int, int>(70, 70));
	m.insert(ft::make_pair<int, int>(80, 80));
	m.printTree();
	std::cout << "\nINSERTION TESTS: OK\n";
	return ;
}

void	erase(void)
{
	ft::map<int, int>	m;
	std::size_t			res;
	/*
	**	Pensar cómo comprobar con las funciones públicas de map
	**	que un árbol es correcto.
	**
	**	IDEAS
	**
	**	1. Recorrerlo en orden y comprobar que el orden es correcto.
	**	2. Comprobar key de extremos (first y last iterator)
	*/
	m.insert(ft::make_pair<int, int>(10, 10));
	m.insert(ft::make_pair<int, int>(20, 20));
	m.insert(ft::make_pair<int, int>(30, 30));
	m.insert(ft::make_pair<int, int>(40, 40));
	m.insert(ft::make_pair<int, int>(50, 50));
	m.insert(ft::make_pair<int, int>(60, 60));
	res = m.erase(30);
	assert(res == 1);
	res = m.erase(50);
	assert(res == 1);
	res = m.erase(42);
	assert(!res);
	res = m.erase(20);
	assert(res == 1);
	res = m.erase(40);
	assert(res == 1);
	res = m.erase(10);
	assert(res == 1);
	res = m.erase(60);
	assert(res == 1);
	assert(m.empty() == true);
	std::cout << "\nERASE TESTS: OK\n";
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

void	observers(void)
{
	ft::map<int, std::string>				m;
	ft::map<int, std::string>::iterator		it;
	ft::map<int, std::string>::key_compare	cmp;

	m.insert(ft::pair<int, std::string>(1, "a"));
	m.insert(ft::pair<int, std::string>(2, "b"));
	cmp = m.key_comp();
	it = m.end();
	--it;
	assert(cmp(m.begin()->first, it->first));
	std::cout << "\nOBSERVERS TESTS: OK\n";
	return ;
}

int	main(void)
{
	construction();
	insertion();
	erase();
	access();
	observers();
	std::cout << std::endl;
	return (0);
}