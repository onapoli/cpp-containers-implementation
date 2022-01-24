#include <iostream>
#include <typeinfo>

#include "./containers/vector.hpp"
#include "./type_traits/type_traits.hpp"

// default, fill, range and copy Contructor tests.
void	construction(void)
{
	std::cout << "\n\n--- CONSTRUCTION TESTS ---\n";

	ft::vector<int>	v;
	ft::vector<int>	v2(2);
	ft::vector<int>	v3(3, 1);
	ft::vector<int>	v4(v3);
	ft::vector<int>	v5(v4.begin(), v4.end());
	int	a[3] = {1, 2, 3};
	ft::vector<int>	v6(a, a + 3);

	std::cout << "v size: " << v.size() << "\n";
	std::cout << "v2 size: " << v2.size() << "\n";
	std::cout << "v3 size: " << v3.size() << "\n";
	std::cout << "v4 size: " << v4.size() << "\n";
	std::cout << "v5 size: " << v5.size() << "\n";
	std::cout << "v6 size: " << v6.size() << "\n";
	std::cout << "v6.at(1) " << v6.at(1) << "\n";
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
	std::cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << "\n";
	std::cout << "vs: " << vs << "\n";
	std::cout << "v.max_size(): " << v.max_size() << std::endl;
	std::cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << "\n";
	v2.resize(8);
	std::cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << "\n";
	v2.resize(7);
	std::cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << "\n";
	v2.resize(4);
	std::cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << "\n";
	v2.resize(20);
	std::cout << "v2.size(): " << v2.size() << ", v2.capacity(): " << v2.capacity() << "\n";
	return ;
}

void	access(void)
{
	std::cout << "\n\n--- ACCESS TESTS ---\n";
	ft::vector<int> v(5, 1);
	ft::vector<int> const v2(2);

	std::cout << "v.front(): " << v.front() << "\n";
	std::cout << "v2.front(): " << v2.front() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	std::cout << "v2.back(): " << v2.back() << "\n";
	std::cout << "v.at(4): " << v.at(4) << "\n";
	try
	{
		std::cout << "v2.at(4): " << v2.at(5) << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << "\nERROR: " << e.what() << '\n';
	}
	std::cout << "v[4]: " << v[4] << "\n";
	std::cout << "v2[4] (Undefined behaviour!!): " << v2[4] << "\n";
	return ;
}

void	exception(void)
{
	return ;
}

void	iterator(void)
{
	std::cout << "\n\n--- ITERATOR TESTS ---\n";
	ft::vector<int>				v;
	ft::vector<int>::iterator	it;
	ft::vector<int>				v2(2, 1);

	it = v.begin();
	if (it == v.begin())
		std::cout << "Equal\n";
	it = v.end();
	if (it == v.begin())
		std::cout << "Equal\n";
	//ERROR (Seg.Fault) Trying to access unallocated memory:
	//std::cout << "end value: " << *it << std::endl;
	it = v2.begin();
	*it = 42;
	std::cout << "v2[0]: " << v2[0] << "\n";
	std::cout << "*it: " << *it << "\n";
	++it;
	std::cout << "*it: " << *it << "\n";
	it = v2.begin();
	it++;
	std::cout << "*it: " << *it << "\n";
	it = v2.begin();
	std::cout << "*it++: " << *it++ << "\n";
	std::cout << "*it: " << *it << "\n";
	return ;
}

void	iterator_arithmetic(void)
{
	std::cout << "\n\n--- ITERATOR ARITHMETIC TESTS ---\n";
	ft::vector<int>			v(5, 1);
	ft::vector<int>::iterator	it;
	ft::vector<int>::iterator	it2;

	for (int i = 0; v.begin() + i != v.end(); ++i)
		*(v.begin() + i) = i;
	it = v.begin();
	it2 = v.begin() + 2;
	std::cout << *it << "\n";
	std::cout << *(it + 1) << "\n";
	std::cout << *it << "\n";
	*(it + 1) = 42;
	std::cout << v[1] << "\n";
	it2 = it + 1;
	std::cout << *it2 << "\n";
	*(it + 1) = 1;
	it2 = v.begin() + 3;
	std::cout << it2 - it << "\n";
	return ;
}

void	iterator_constness(void)
{
	std::cout << "\n\n--- ITERATOR CONSTNESS TESTS ---\n";
	ft::vector<int> const			v(2, 1);
	ft::vector<int>::const_iterator	cit;

	for (cit = v.begin(); cit != v.end(); ++cit)
	{
		std::cout << *cit << "\n";
	}
	cit = v.begin();
	//*cit = 2; DOES NOT COMPILE
	return ;
}

void	iter_traits(void)
{
	std::cout << "\n\n--- ITERATOR TRAITS TESTS ---\n";
	typedef ft::vector<int>::iterator						my_iter_type;
	ft::iterator_traits<my_iter_type>::iterator_category	cat;
	ft::iterator_traits<int*>::iterator_category			cat2;

	std::cout << "Is ft::vector<int>::iterator a random_access_iterator? ";
	std::cout << (typeid(cat) == typeid(std::random_access_iterator_tag)) << "\n";
	std::cout << "Is int* a random_access_iterator? ";
	std::cout << (typeid(cat2) == typeid(std::random_access_iterator_tag)) << "\n";	
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

	i = 0;
	for (it = v.begin(); it != v.end(); ++it)
		*it = i++;
	std::cout << "The first dereference of rit.base()";
	std::cout << " will generate an invalid read WARNING." << "\n";
	for (; rit != rit2; ++rit)
		std::cout << "value: " << *rit << " base: " << *(rit.base()) << "\n";
	return ;
}

void	modifier_assign(void)
{
	std::cout << "\n\n--- ASSIGN TESTS ---\n";
	ft::vector<int>	v;
	ft::vector<int>	v2(2, 24);

	v.assign(5, 42);
	std::cout << "v.size(): " << v.size() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	v.assign(v2.begin(), v2.end());
	std::cout << "v.size(): " << v.size() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	return ;
}

void	modifier_push_pop_back(void)
{
	std::cout << "\n\n--- PUSH && POP TESTS ---\n";
	ft::vector<int>	v(2, 100);

	std::cout << "v.capacity(): " << v.capacity();
	std::cout << " v.size(): " << v.size() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	v.push_back(42);
	std::cout << "EXECUTE v.push_back(42)" << "\n";
	std::cout << "v.capacity(): " << v.capacity();
	std::cout << " v.size(): " << v.size() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	v.pop_back();
	std::cout << "EXECUTE v.pop_back()" << "\n";
	std::cout << "v.capacity(): " << v.capacity();
	std::cout << " v.size(): " << v.size() << "\n";
	std::cout << "v.back(): " << v.back() << "\n";
	return ;
}

void	modifier_insert(void)
{
	std::cout << "\n\n--- MODIFIER INSERT TESTS ---\n";
	ft::vector<int>				v(4, 42);
	ft::vector<int>				v2(5, 5000);
	ft::vector<int>::iterator	it;

	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	std::cout << "\nEXECUTED v.insert(v.begin() + 2, 24)\n" << "\n";
	v.insert(v.begin() + 2, 24);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.begin(), 80)\n" << "\n";
	v.insert(v.begin(), 80);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.end(), 80)\n" << "\n";
	v.insert(v.end(), 80);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.begin() + 4, 2, 100)\n" << "\n";
	v.insert(v.begin() + 4, 2, 100);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.begin(), 1, 42000)\n" << "\n";
	v.insert(v.begin(), 1, 42000);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.end(), 2, 42000)\n" << "\n";
	v.insert(v.end(), 2, 42000);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	std::cout << "\nEXECUTED v.insert(v.begin() + 5, v2.begin(), v2.end())\n" << "\n";
	v.insert(v.begin() + 5, v2.begin(), v2.end());
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	return ;
}

void	modifier_erase(void)
{
	std::cout << "\n\n--- MODIFIER ERASE TESTS ---\n";
	ft::vector<int>				v(5, 500);
	ft::vector<int>::iterator	it;
	int							i;

	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(), i = 0; it != v.end(); ++it, ++i)
	{
		*it = i;
		std::cout << "index: " << i << " value: " << *it << "\n";
	}
	std::cout << "EXECUTED v.erase(v.begin() + 2)" << "\n";
	v.erase(v.begin() + 2);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(), i = 0; it != v.end(); ++it, ++i)
	{
		std::cout << "index: " << i << " value: " << *it << "\n";
	}
	std::cout << "EXECUTED v.erase(v.begin())" << "\n";
	v.erase(v.begin());
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(), i = 0; it != v.end(); ++it, ++i)
	{
		std::cout << "index: " << i << " value: " << *it << "\n";
	}
	std::cout << "EXECUTED v.erase(v.begin())" << "\n";
	v.erase(v.end() - 1);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(), i = 0; it != v.end(); ++it, ++i)
	{
		std::cout << "index: " << i << " value: " << *it << "\n";
	}
	return ;
}

void	modifier_swap(void)
{
	std::cout << "\n\n--- MODIFIER SWAP TESTS ---\n";
	ft::vector<int>				v(5, 500);
	ft::vector<int>				v2(2, 200);
	ft::vector<int>::iterator	it;

	std::cout << "vector v:\n";
	std::cout << "v.size(): " << v.size() << " v.capacity(): ";
	std::cout << v.capacity() << "\n";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << "index " << it - v.begin() << ": " << *it << "\n";
	}
	std::cout << "vector v2:\n";
	std::cout << "v2.size(): " << v2.size() << " v2.capacity(): ";
	std::cout << v2.capacity() << "\n";
	for (it = v2.begin(); it != v2.end(); ++it)
	{
		std::cout << "index " << it - v2.begin() << ": " << *it << "\n";
	}
	v.swap(v2);
	std::cout << "\nEXECUTED v.swap(v2)\n\n";
	std::cout << "vector v:\n";
	std::cout << "v.size(): " << v.size() << " v.capacity(): ";
	std::cout << v.capacity() << "\n";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << "index " << it - v.begin() << ": " << *it << "\n";
	}
	std::cout << "vector v2:\n";
	std::cout << "v2.size(): " << v2.size() << " v2.capacity(): ";
	std::cout << v2.capacity() << "\n";
	for (it = v2.begin(); it != v2.end(); ++it)
	{
		std::cout << "index " << it - v2.begin() << ": " << *it << "\n";
	}
	return ;
}

void	non_member_swap(void)
{
	std::cout << "\n\n--- MODIFIER SWAP TESTS ---\n";
	ft::vector<int>				v(5, 500);
	ft::vector<int>				v2(2, 200);
	ft::vector<int>::iterator	it;

	std::cout << "vector v:\n";
	std::cout << "v.size(): " << v.size() << " v.capacity(): ";
	std::cout << v.capacity() << "\n";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << "index " << it - v.begin() << ": " << *it << "\n";
	}
	std::cout << "vector v2:\n";
	std::cout << "v2.size(): " << v2.size() << " v2.capacity(): ";
	std::cout << v2.capacity() << "\n";
	for (it = v2.begin(); it != v2.end(); ++it)
	{
		std::cout << "index " << it - v2.begin() << ": " << *it << "\n";
	}
	ft::swap(v, v2);
	std::cout << "\nEXECUTED ft::swap(v, v2)\n\n";
	std::cout << "vector v:\n";
	std::cout << "v.size(): " << v.size() << " v.capacity(): ";
	std::cout << v.capacity() << "\n";
	for (it = v.begin(); it != v.end(); ++it)
	{
		std::cout << "index " << it - v.begin() << ": " << *it << "\n";
	}
	std::cout << "vector v2:\n";
	std::cout << "v2.size(): " << v2.size() << " v2.capacity(): ";
	std::cout << v2.capacity() << "\n";
	for (it = v2.begin(); it != v2.end(); ++it)
	{
		std::cout << "index " << it - v2.begin() << ": " << *it << "\n";
	}
	return ;
}

void	non_member_relational(void)
{
	std::cout << "\n\n--- RELATIONAL TESTS ---\n";
	ft::vector<int>	v(2, 200);
	ft::vector<int>	v2(v);

	std::cout << "v(2, 200)\nv2(v)\n";
	std::cout << std::boolalpha;
	std::cout << "v == v2 ? " << (v == v2) << "\n";
	std::cout << "v >= v2 ? " << (v >= v2) << "\n";
	std::cout << "v != v2 ? " << (v != v2) << "\n";
	v.back() = 201;
	std::cout << "\nEXECUTED v.back() = 201\n\n";
	std::cout << "v > v2 ? " << (v > v2) << "\n";
	std::cout << "v < v2 ? " << (v < v2) << "\n";
	v2.push_back(200);
	std::cout << "\nEXECUTED v2.push_back(200)\n\n";
	std::cout << "v > v2 ? " << (v > v2) << "\n";
	std::cout << "v < v2 ? " << (v < v2) << "\n";
	v.back() = 200;
	std::cout << "\nEXECUTED v.back() = 200\n\n";
	std::cout << "v > v2 ? " << (v > v2) << "\n";
	std::cout << "v < v2 ? " << (v < v2) << "\n";
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
	return (0);
}