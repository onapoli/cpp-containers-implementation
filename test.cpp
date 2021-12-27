#include "vector.hpp"

// default, fill, range and copy Contructor tests.
void	construction(void)
{
	std::cout << "\n\n--- CONSTRUCTION TESTS ---\n";

	ft::vector<int>	v;
	ft::vector<int>	v2(2);
	ft::vector<int>	v3(3, 1);
	ft::vector<int>	v4(v3);
	//ASSIGNMENT AND RANGE TESTS STILL MISSING ...

	std::cout << "v size: " << v.size() << "\n";
	std::cout << "v2 size: " << v2.size() << "\n";
	std::cout << "v3 size: " << v3.size() << "\n";
	std::cout << "v4 size: " << v4.size() << "\n";
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

void	exceptions(void)
{
	return ;
}

int	main(void)
{
	construction();
	size();
	access();
	exceptions();
	return (0);
}