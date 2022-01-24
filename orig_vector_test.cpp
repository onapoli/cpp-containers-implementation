#include <iostream>
#include <vector>

void	range_constructor(void)
{
	std::cout << "\n\n--- RANGE CONSTRUCTOR TESTS ---\n";
	std::vector<int>	v(4, 42);
	std::vector<int>	v2(v.begin(), v.end());
	std::vector<int>	v3(int, float);

	std::cout << "v.size(): " << v.size() << "\n";
	std::cout << "v2.size(): " << v2.size() << "\n";
	std::cout << "v.capacity(): " << v.capacity() << "\n";
	std::cout << "v2.capacity(): " << v2.capacity() << "\n";
	//std::cout << "v3.size(): " << v3.size() << "\n";
	std::cout << "v.front() " << v.front() << "\n";
	std::cout << "v2.front()" << v2.front() << "\n";
	return ;
}

void	iterator(void)
{
	std::cout << "\n\n--- ITERATOR TESTS ---\n";
	std::vector<int>	v;
	std::vector<int>::iterator	it;

	it = v.begin();
	if (it == v.begin())
		std::cout << "Equal\n";
	it = v.end();
	if (it == v.begin())
		std::cout << "Equal\n";
	//std::cout << "end value: " << *it << std::endl;
	return ;
}

void	iterator_2(void)
{
	std::cout << "\n\n--- ITERATOR_2 TESTS ---\n";
	std::vector<int>			v(5, 1);
	std::vector<int>::iterator	it;

	it = v.begin();
	*it = 42;
	std::cout << "*it: " << *it << "\n";
	std::cout << "*it++: " << *it++ << "\n";
	std::cout << "*it: " << *it << "\n";
	it = v.begin();
	std::cout << *it << "\n";
	--it;
	std::cout << *it << "\n";
	--it;
	std::cout << *it << "\n";
	std::cout << "v[-1]: " << v[-1] << "\n";
	std::cout << "v[-2]: " << v[-2] << "\n";
	return ;
}

void	iterator_3(void)
{
	std::cout << "\n\n--- ITERATOR_3 TESTS ---\n";
	std::vector<int>			v(5, 1);
	std::vector<int>::iterator	it;
	std::vector<int>::iterator	it2;

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
	std::cout << "it2 - it: " << it2 - it << "\n";
	*it = 24;
	std::cout << "*(it -= 100): " << *(it -= 100) << "\n";
	std::cout << *(it + 90) << "\n";
	std::cout << *(it + 100) << "\n";
	std::cout << it[100] << "\n";
	return ;
}

void	const_iter(void)
{
	std::vector<int>					v(2, 1);
	std::vector<int>::iterator			it;
	std::vector<int>::const_iterator	cit;

	std::cout << "\n\n--- CONST ITERATOR TESTS ---\n";
	it = v.begin();
	cit = v.begin();
	if (it == cit)
		std::cout << "Equal\n";
	if (cit == it)
		std::cout << "Equal\n";
	return ;
}

void	iter_traits(void)
{
	std::cout << "\n\n--- ITER TRAITS TESTS ---\n";
	std::vector<int>			v(2, 1);
	std::vector<int>::iterator	it;

	it = v.begin();
	return ;
}

void	reverse_iter(void)
{
	std::cout << "\n\n--- REVERSE ITERATOR TESTS ---\n";
	std::vector<int>					v(5, 0);
	std::size_t							i;
	std::vector<int>::iterator			it;
	std::vector<int>::reverse_iterator	rit(v.end());
	std::vector<int>::reverse_iterator	rit2(v.begin());

	i = 0;
	for (it = v.begin(); it != v.end(); ++it)
		*it = i++;
	for (; rit != rit2; ++rit)
		std::cout << "value: " << *rit << " base: " << *(rit.base()) << "\n";
	return ;
}

void	push_pop(void)
{
	std::cout << "\n\n--- PUSH POP TESTS ---\n";
	std::vector<int>	v(2, 100);

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

void	insert(void)
{
	std::cout << "\n\n--- INSERT TESTS ---\n";
	std::vector<int>			v(2, 100);
	std::vector<int>::iterator	it;

	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	v.insert(v.end(), 2, 200);
	std::cout << "v.size(): " << v.size() << " v.capacity(): " << v.capacity() << "\n";
	for (it = v.begin(); it < v.end(); ++it)
	{
		std::cout << "index: " << it - v.begin() << " val: " << *it << "\n";
	}
	return ;
}

void	non_member_relational(void)
{
	std::cout << "\n\n--- RELATIONAL TESTS ---\n";
	std::vector<int>	v(2, 200);
	std::vector<int>	v2(v);

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
	range_constructor();
	iterator();
	iterator_2();
	iterator_3();
	const_iter();
	iter_traits();
	reverse_iter();
	push_pop();
	insert();
	non_member_relational();
	return (0);
}