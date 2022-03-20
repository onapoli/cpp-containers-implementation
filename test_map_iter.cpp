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
	assert(it == it2);
	--it;
	--it2;
	assert(it == it2);
	assert((*it).first == 30);
	assert((*it2).first == 30);
	std::cout << m.max_size() << std::endl;
	std::cout << "\nCOMPARISON TESTS: OK\n";
	return ;
}

void	constness(void)
{
	ft::map<int, int>					m;
	ft::map<int, int>::iterator			it;
	ft::map<int, int>::const_iterator	cit(it);
	//COMPILATION ERROR, AS iterator CANNOT COPY const_iterator
	//ft::map<int, int>::iterator			it2(cit);
	ft::map<int, int>::iterator			it2;
	int									counter;

	m.insert(ft::pair<int, int>(10, 10));
	m.insert(ft::pair<int, int>(20, 20));
	it = m.begin();
	cit = it;
	it2 = it;
	//COMPILATION ERROR, AS iterator CANNOT BE ASSIGNED const_iterator
	//it = cit;
	counter = 10;
	for (cit = m.begin(); cit != m.end(); ++cit)
	{
		//COMPILATION ERROR, AS cit IS CONST
		//*cit = ft::pair<int, int>(2, 2);
		assert(counter == cit->first);
		counter += 10;
	}
	std::cout << "\nCONSTNESS TESTS: OK\n";
	return ;
}

void	reverse(void)
{
	ft::map<int, int>					m;
	ft::map<int, int>::reverse_iterator	rit;
	int									counter;

	m.insert(ft::pair<int, int>(1, 1));
	m.insert(ft::pair<int, int>(2, 2));
	m.insert(ft::pair<int, int>(3, 3));
	rit = m.rbegin();
	//COMPILATION ERROR. KEYS CANNOT BE MODIFIED. THEY ARE CONST
	//rit->first = 3;
	rit->second = 3;
	(*rit).second = 3;
	counter = 3;
	for (rit = m.rbegin(); rit != m.rend(); ++rit)
	{
		assert(rit->first == counter);
		--counter;
	}
	// COMPILATION ERROR: INVALID OPERANDS FOR bidirectional iterator
	//assert( (rit < m.rbegin()) == false );
	std::cout << "\nREVERSE TESTS: OK\n";
	return ;
}

void	reverse_constness(void)
{
	ft::map<int, int>							m;
	ft::map<int, int>::reverse_iterator			rit;
	ft::map<int, int>::const_reverse_iterator	crit(rit);
	//COMPILATION ERROR, AS iterator CANNOT COPY const_iterator
	//ft::map<int, int>::iterator				rit2(crit);
	ft::map<int, int>::reverse_iterator			rit2;
	int											counter;

	m.insert(ft::pair<int, int>(10, 10));
	m.insert(ft::pair<int, int>(20, 20));
	rit = m.rbegin();
	//COMPILATION ERROR. KEYS CANNOT BE MODIFIED. THEY ARE CONST
	//rit->first = 20;
	rit->second = 20;
	(*rit).second = 20;
	crit = rit;
	rit2 = rit;
	//COMPILATION ERROR, AS iterator CANNOT BE ASSIGNED const_iterator
	//rit = crit;
	counter = 20;
	for (crit = m.rbegin(); crit != m.rend(); ++crit)
	{
		//COMPILATION ERROR, AS crit IS CONST
		//*crit = ft::pair<int, int>(2, 2);
		assert(counter == crit->first);
		counter -= 10;
	}
	return ;
}

int	main(void)
{
	construction();
	add_sub();
	comparison();
	constness();
	reverse();
	reverse_constness();
	std::cout << std::endl;
	return (0);
}