#include <iostream>
#include <assert.h>

#include "containers/map.hpp"

void	construction(void)
{
	ft::map<int, std::string>							m;
	ft::map<int, std::string>::iterator					it;
	ft::pair<ft::map<int, std::string>::iterator, bool>	pr;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	assert(!m.empty());
	assert(m.size() == 1);
	pr = m.insert(ft::make_pair<int, std::string>(5, "hello"));
	assert(pr.second == false);
	assert(m.size() == 1);
	m.insert(ft::make_pair<int, std::string>(1, "bye"));
	assert(m.size() == 2);
	ft::map<int, std::string>	m2(m);
	assert(m2.size() == 2);
	assert(m2.begin()->first == 1);
	m2.begin()->second = "adios";
	assert(m2.begin()->second == "adios");
	assert(m.begin()->second == "bye");
	ft::map<int, std::string>	m3(m.begin(), m.end());
	assert(m3.size() == 2);
	assert(m3.begin()->first == 1);
	it = m.begin();
	++it;
	assert(it->first == 5);
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
	m.insert(ft::make_pair<int, int>(50, 50));
	m.insert(ft::make_pair<int, int>(60, 60));
	m.insert(ft::make_pair<int, int>(70, 70));
	m.insert(ft::make_pair<int, int>(80, 80));
	std::cout << "\nINSERTION TESTS: OK\n";
	return ;
}

void	insertion_iter(void)
{
	ft::map<int, int>			m;
	ft::map<int, int>			m2;
	ft::map<int, int>::iterator	it;
	int							counter;

	m.insert(ft::pair<int, int>(20, 20));
	it = m.begin();
	m.insert(it, ft::pair<int, int>(30, 30));
	m.insert(it, ft::pair<int, int>(10, 10));
	it = m.find(30);
	m.insert(it, ft::pair<int, int>(40, 40));
	//BAD PERFORMANCE BECAUSE OF BAD HINT
	m.insert(it, ft::pair<int, int>(50, 50));
	m.insert(it, ft::pair<int, int>(60, 60));
	assert(m.size() == 6);
	counter = 10;
	for (it = m.begin(); it != m.end(); ++it)
	{
		assert(it->first == counter);
		counter += 10;
	}
	m2.insert(m.begin(), m.upper_bound(40));
	assert(m2.size() == 4);
	counter = 10;
	for (it = m2.begin(); it != m2.end(); ++it)
	{
		assert(it->first == counter);
		counter += 10;
	}
	std::cout << "\nINSERTION WITH ITERATORS TESTS: OK\n";
	return ;
}

void	erase_key(void)
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
	std::cout << "\nERASE KEY TESTS: OK\n";
	return ;
}

void	erase_iter(void)
{
	ft::map<int, int>			m;
	ft::map<int, int>::iterator	it;
	int							counter;

	m.insert(ft::make_pair<int, int>(10, 10));
	m.insert(ft::make_pair<int, int>(20, 20));
	m.insert(ft::make_pair<int, int>(30, 30));
	m.insert(ft::make_pair<int, int>(40, 40));
	m.insert(ft::make_pair<int, int>(50, 50));
	m.insert(ft::make_pair<int, int>(60, 60));
	m.erase(m.find(50));
	m.erase(m.lower_bound(40), m.upper_bound(60));
	counter = 10;
	for (it = m.begin(); it != m.end(); ++it)
	{
		assert(it->first == counter);
		counter += 10;
	}
	std::cout << "\nERASE ITER TESTS: OK\n";
	return ;
}

void	swapping(void)
{
	ft::map<int, std::string>	m;
	ft::map<int, std::string>	n;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	n.insert(ft::make_pair<int, std::string>(10, "bye"));
	n.insert(ft::make_pair<int, std::string>(15, "au revoir"));
	m.swap(n);
	assert(m.size() == 2);
	assert(n.size() == 1);
	assert(m.begin()->first == 10 && m.begin()->second == "bye");
	assert(n.begin()->first == 5 && n.begin()->second == "hello");
	std::cout << "\nSWAP TESTS: OK\n";
	return ;
}

void	clear(void)
{
	ft::map<int, int>	m;

	m.insert(ft::make_pair<int, int>(10, 10));
	m.insert(ft::make_pair<int, int>(20, 20));
	m.insert(ft::make_pair<int, int>(30, 30));
	m.insert(ft::make_pair<int, int>(40, 40));
	m.insert(ft::make_pair<int, int>(50, 50));
	m.insert(ft::make_pair<int, int>(60, 60));
	m.clear();
	assert(m.size() == 0);
	std::cout << "\nCLEAR TESTS: OK\n";
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
	m[10] = "alo";
	assert(m.count(10) == 1);
	assert(m[10] == "alo");
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
	assert(m.value_comp()(*(m.begin()), *(m.find(2))) == true);
	assert(m.value_comp()(*(m.find(2)), *(m.begin())) == false);
	std::cout << "\nOBSERVERS TESTS: OK\n";
	return ;
}

void	find_count(void)
{
	ft::map<int, std::string>				m;
	ft::map<int, std::string>::iterator		it;

	m.insert(ft::pair<int, std::string>(1, "a"));
	m.insert(ft::pair<int, std::string>(2, "b"));
	it = m.find(2);
	assert(it != m.end());
	it = m.find(42);
	assert(it == m.end());
	assert(m.count(1) == 1);
	assert(m.count(42) == 0);
	std::cout << "\nFIND COUNT TESTS: OK\n";
	return ;
}

void	bounds(void)
{
	ft::map<int, std::string>				m;
	ft::map<int, std::string>::iterator		it;

	m.insert(ft::pair<int, std::string>(1, "a"));
	m.insert(ft::pair<int, std::string>(5, "e"));
	m.insert(ft::pair<int, std::string>(10, "j"));
	m.insert(ft::pair<int, std::string>(13, "m"));
	it = m.lower_bound(2);
	assert(it->first == 5);
	it = m.lower_bound(10);
	assert(it->first == 10);
	it = m.lower_bound(42);
	assert(it == m.end());
	it = m.upper_bound(5);
	assert(it->first == 10);
	it = m.upper_bound(8);
	assert(it->first == 10);
	it = m.upper_bound(15);
	assert(it == m.end());
	std::cout << "\nBOUNDS TESTS: OK\n";
	return ;
}

void	equal_range(void)
{
	ft::map<int, std::string>						m;
	ft::map<int, std::string>::iterator				it;
	ft::pair<ft::map<int, std::string>::iterator,
		ft::map<int, std::string>::iterator>		pr;

	m.insert(ft::pair<int, std::string>(1, "a"));
	m.insert(ft::pair<int, std::string>(5, "e"));
	m.insert(ft::pair<int, std::string>(10, "j"));
	m.insert(ft::pair<int, std::string>(13, "m"));
	pr = m.equal_range(5);
	assert((pr.first)->first == 5);
	assert((pr.second)->first == 10);
	pr = m.equal_range(42);
	assert(pr.first == pr.second);
	assert(pr.first == m.end());
	std::cout << "\nEQUAL RANGE TESTS: OK\n";
	return ;
}

void	non_member_swap()
{
	ft::map<int, std::string>	m;
	ft::map<int, std::string>	n;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	n.insert(ft::make_pair<int, std::string>(10, "bye"));
	n.insert(ft::make_pair<int, std::string>(15, "au revoir"));
	ft::swap(m, n);
	assert(m.size() == 2);
	assert(n.size() == 1);
	assert(m.begin()->first == 10 && m.begin()->second == "bye");
	assert(n.begin()->first == 5 && n.begin()->second == "hello");
	std::cout << "\nNON-MEMBER SWAP TESTS: OK\n";
	return ;
}

void	non_member_relational()
{
	ft::map<int, std::string>	m;
	ft::map<int, std::string>	n;

	m.insert(ft::make_pair<int, std::string>(5, "hello"));
	n.insert(ft::make_pair<int, std::string>(10, "bye"));
	n.insert(ft::make_pair<int, std::string>(15, "au revoir"));
	assert( (m < n) == true);
	assert( (m > n) == false);
	assert( (m >= n) == false);
	assert( (m <= n) == true);
	assert( (m == n) == false);
	assert( (m != n) == true);
	n = m;
	assert( (n == m) == true);
	assert( (m == n) == true);
	assert( (n != m) == false);
	assert( (n <= m) == true);
	assert( (n >= m) == true);
	return ;
}

int	main(void)
{
	construction();
	insertion();
	insertion_iter();
	erase_key();
	erase_iter();
	swapping();
	clear();
	access();
	observers();
	find_count();
	bounds();
	equal_range();
	non_member_swap();
	non_member_relational();
	std::cout << std::endl;
	return (0);
}