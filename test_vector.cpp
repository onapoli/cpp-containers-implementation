#include <iostream>
#include <typeinfo>
#include <cassert>

#include "./containers/vector.hpp"
#include "./type_traits/type_traits.hpp"

// default, fill, range and copy Contructor tests.
void	construction(void)
{
	ft::vector<int>	v;
	ft::vector<int>	v2(2);
	ft::vector<int>	v3(3, 1);
	ft::vector<int>	v4(v3);
	ft::vector<int>	v5(v4.begin(), v4.end());
	int	a[3] = {1, 2, 3};
	ft::vector<int>	v6(a, a + 3);

	assert(v.size() == 0);
	assert(v2.size() == 2);
	assert(v3.size() == 3);
	assert(v4.size() == 3);
	assert(v5.size() == 3);
	assert(v6.size() == 3);
	assert(v6.at(1) == 2);
	std::cout << "\nCONSTRUCTION TESTS: OK\n";
	return ;
}

// size_type, size(), resize() tests.
void	size(void)
{
	std::cout << "\n\n--- SIZE TESTS ---\n";

	ft::vector<int>				v;
	ft::vector<int>::size_type	vs;
	ft::vector<int>				v2(5);

	vs = v.size();
	assert(v.size() == 0 && v.capacity() == 0);
	assert(vs == 0);
	std::cout << "v.max_size(): " << v.max_size() << std::endl;
	assert(v2.size() == 5 && v2.capacity() == 5);
	v2.resize(8);
	assert(v2.size() == 8 && v2.capacity() == 10);
	v2.resize(7);
	assert(v2.size() == 7 && v2.capacity() == 10);
	v2.resize(4);
	assert(v2.size() == 4 && v2.capacity() == 8);
	v2.resize(20);
	assert(v2.size() == 20 && v2.capacity() == 20);
	std::cout << "\nSIZE TESTS: OK\n";
	return ;
}

void	access(void)
{
	std::cout << "\n\n--- ACCESS TESTS ---\n";
	ft::vector<int> v(5, 1);
	ft::vector<int> const v2(2);

	assert(v.front() == 1);
	assert(v2.front() == 0);
	assert(v.back() == 1);
	assert(v2.back() == 0);
	assert(v.at(4) == 1);
	try
	{
		std::cout << "v2.at(4): " << v2.at(5) << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << "\nEXPECTED ERROR: " << e.what() << '\n';
	}
	assert(v[4] == 1);
	std::cout << "v2[4] (Undefined behaviour!!): " << v2[4] << "\n";
	std::cout << "\nACCESS TESTS: OK\n";
	return ;
}

void	exception(void)
{
	return ;
}

void	iterator(void)
{
	ft::vector<int>				v;
	ft::vector<int>::iterator	it;
	ft::vector<int>				v2(2, 1);

	it = v.begin();
	assert(it == v.begin());
	it = v.end();
	assert(it == v.begin());
	//ERROR (Seg.Fault) Trying to access non-allocated memory:
	//std::cout << "end value: " << *it << std::endl;
	it = v2.begin();
	*it = 42;
	assert(v2[0] == 42);
	assert(*it == 42);
	++it;
	assert(*it == 1);
	it = v2.begin();
	it++;
	assert(*it == 1);
	it = v2.begin();
	assert(*it++ == 42);
	assert(*it == 1);
	std::cout << "\nITERATOR TESTS: OK\n";
	return ;
}

void	iterator_arithmetic(void)
{
	ft::vector<int>			v(5, 1);
	ft::vector<int>::iterator	it;
	ft::vector<int>::iterator	it2;

	for (int i = 0; v.begin() + i != v.end(); ++i)
		*(v.begin() + i) = i;
	it = v.begin();
	it2 = v.begin() + 2;
	assert(*it == 0);
	assert(*(it + 1) == 1);
	assert(*it == 0);
	*(it + 1) = 42;
	assert(v[1] == 42);
	it2 = it + 1;
	assert(*it2 == 42);
	*(it + 1) = 1;
	it2 = v.begin() + 3;
	assert(it2 - it == 3);
	std::cout << "\nITERATOR ARITHMETIC TESTS: OK\n";
	return ;
}

void	iterator_constness(void)
{
	ft::vector<int>					v(2, 1);
	ft::vector<int>::iterator		it;
	ft::vector<int>::const_iterator	cit;
	//DOES NOT COMPILE
	//ft::vector<int>::iterator		it2(cit);
	ft::vector<int>::const_iterator	cit2(it);

	it = v.begin();
	cit = it;
	//DOES NOT COMPILE
	//it = cit;
	cit2 = cit;
	for (cit = v.begin(); cit != v.end(); ++cit)
	{
		assert(*cit == 1);
	}
	cit = v.begin();
	//DOES NOT COMPILE
	// *cit = 2;
	std::cout << "\nITERATOR CONSTNESS TESTS: OK\n";
	return ;
}

void	iter_traits(void)
{
	typedef ft::vector<int>::iterator						my_iter_type;
	ft::iterator_traits<my_iter_type>::iterator_category	cat;
	ft::iterator_traits<int*>::iterator_category			cat2;

	assert( (typeid(cat) == typeid(std::random_access_iterator_tag) ) == true);
	assert( (typeid(cat2) == typeid(std::random_access_iterator_tag) ) == true);
	assert( (typeid(int) == typeid(std::random_access_iterator_tag) ) == false);
	std::cout << "\nITERATOR TRAITS TESTS: OK\n";
	return ;
}

void	rev_iter(void)
{
	std::cout << "\n\n--- REVERSE ITERATOR TESTS ---\n";
	ft::vector<int>						v(5, 0);
	std::size_t							i;
	ft::vector<int>::iterator			it;
	ft::vector<int>::reverse_iterator	rit(v.end());
	ft::vector<int>::reverse_iterator	rit2(v.begin());
	int									counter;
	int									base_counter;

	i = 0;
	for (it = v.begin(); it != v.end(); ++it)
		*it = i++;
	std::cout << "The first dereference of rit.base()";
	std::cout << " will generate an invalid read WARNING";
	std::cout << " in memory inspector." << "\n";
	counter = 4;
	base_counter = 5;
	for (; rit != rit2; ++rit)
	{
		std::cout << "value: " << *rit << " base: " << *(rit.base()) << "\n";
		if (counter == 4)
			assert(*rit == counter && *(rit.base()) == 0);
		else
			assert(*rit == counter && *(rit.base()) == base_counter);
		--counter;
		--base_counter;
	}
	std::cout << "\nREVERSE ITERATOR TESTS: OK\n";
	return ;
}

void	modifier_assign(void)
{
	ft::vector<int>	v;
	ft::vector<int>	v2(2, 24);

	v.assign(5, 42);
	assert(v.size() == 5);
	assert(v.back() == 42);
	v.assign(v2.begin(), v2.end());
	assert(v.size() == 2);
	assert(v.back() == 24);
	std::cout << "\nASSIGN TESTS: OK\n";
	return ;
}

void	modifier_push_pop_back(void)
{
	ft::vector<int>	v(2, 100);

	assert(v.capacity() == 2 && v.size() == 2);
	assert(v.back() == 100);
	v.push_back(42);
	assert(v.capacity() == 4 && v.size() == 3);
	assert(v.back() == 42);
	v.pop_back();
	assert(v.capacity() == 4 && v.size() == 2);
	assert(v.back() == 100);
	std::cout << "\nPUSH && POP TESTS: OK\n";
	return ;
}

void	modifier_insert(void)
{
	ft::vector<int>				v(4, 42);
	ft::vector<int>				v2(5, 5000);
	ft::vector<int>::iterator	it;

	assert(v.size() == 4 && v.capacity() == 4);
	v.insert(v.begin() + 2, 24);
	assert(v.at(2) == 24);
	assert(v.size() == 5 && v.capacity() == 8);
	v.insert(v.begin(), 80);
	assert(v.at(0) == 80);
	assert(v.size() == 6 && v.capacity() == 8);
	v.insert(v.end(), 80);
	assert(v.at(6) == 80);
	assert(v.size() == 7 && v.capacity() == 8);
	v.insert(v.begin() + 4, 2, 100);
	assert(v.at(4) == 100 && v.at(5) == 100);
	assert(v.size() == 9 && v.capacity() == 16);
	v.insert(v.begin(), 1, 42000);
	assert(v.at(0) == 42000);
	assert(v.size() == 10 && v.capacity() == 16);
	v.insert(v.end(), 2, 42000);
	assert(v.at(10) == 42000 && v.at(11) == 42000);
	assert(v.size() == 12 && v.capacity() == 16);
	v.insert(v.begin() + 5, v2.begin(), v2.end());
	assert(v.size() == 17 && v.capacity() == 32);
	for (it = v.begin() + 5; it != v.begin() + 10; ++it)
	{
		assert(*it == 5000);
	}
	std::cout << "\nMODIFIER INSERT TESTS: OK\n";
	return ;
}

void	modifier_erase(void)
{
	ft::vector<int>				v(5, 500);
	ft::vector<int>::iterator	it;
	int							i;
	int							counter;

	assert(v.size() == 5 && v.capacity() == 5);
	counter = 0;
	for (it = v.begin(), i = 0; it != v.end(); ++it, ++i)
	{
		*it = i;
		assert(*it == counter);
		++counter;
	}
	v.erase(v.begin() + 2);
	assert(v.size() == 4 && v.capacity() == 5);
	assert(v.at(2) == 3);
	v.erase(v.begin());
	assert(v.size() == 3 && v.capacity() == 5);
	assert(v.at(0) == 1);
	// ERASES THE LAST ELEMENT. NOT THE PENULTIMATE
	v.erase(v.end() - 1);
	assert(v.size() == 2 && v.capacity() == 4);
	assert(v.at(1) == 3);
	std::cout << "\nMODIFIER ERASE TESTS: OK\n";
	return ;
}

void	modifier_swap(void)
{
	ft::vector<int>				v(5, 500);
	ft::vector<int>				v2(2, 200);
	ft::vector<int>::iterator	it;

	v.swap(v2);
	assert(v.size() == 2 && v.capacity() == 2);
	assert(v.at(0) == 200 && v.at(1) == 200);
	assert(v2.size() == 5 && v2.capacity() == 5);
	assert(v2.at(0) == 500 && v2.at(4) == 500);
	v2.swap(v);
	assert(v.size() == 5 && v.capacity() == 5);
	assert(v.at(0) == 500 && v.at(4) == 500);
	assert(v2.size() == 2 && v2.capacity() == 2);
	assert(v2.at(0) == 200 && v2.at(1) == 200);
	std::cout << "\nMODIFIER SWAP TESTS: OK\n";
	return ;
}

void	non_member_swap(void)
{
	ft::vector<int>				v(5, 500);
	ft::vector<int>				v2(2, 200);
	ft::vector<int>::iterator	it;

	ft::swap(v, v2);
	assert(v.size() == 2 && v.capacity() == 2);
	assert(v.at(0) == 200 && v.at(1) == 200);
	assert(v2.size() == 5 && v2.capacity() == 5);
	assert(v2.at(0) == 500 && v2.at(4) == 500);
	std::cout << "\nNON_MEMBER SWAP TESTS: OK\n";
	return ;
}

void	non_member_relational(void)
{
	ft::vector<int>	v(2, 200);
	ft::vector<int>	v2(v);

	assert( (v == v2) == true);
	assert( (v >= v2) == true);
	assert( (v != v2) == false);
	v.back() = 201;
	assert( (v > v2) == true);
	assert( (v < v2) == false);
	v2.push_back(200);
	assert( (v > v2) == true);
	assert( (v < v2) == false);
	v.back() = 200;
	assert( (v > v2) == false);
	assert( (v < v2) == true);
	std::cout << "\nNON-MEMBER RELATIONAL TESTS\n";
	return ;
}

int	main(void)
{
	construction();
	size();
	access();
	exception();
	iterator();
	iterator_arithmetic();
	iterator_constness();
	iter_traits();
	rev_iter();
	modifier_assign();
	modifier_push_pop_back();
	modifier_insert();
	modifier_erase();
	modifier_swap();
	non_member_swap();
	non_member_relational();
	std::cout << std::endl;
	return (0);
}