#include <iostream>
#include <vector>

int	main(void)
{
	std::vector<int>	v(5);

	std::cout << "size: " << v.size() << ", cap: " << v.capacity() << "\n";
	v.push_back(1);
	v.push_back(1);
	std::cout << "size: " << v.size() << ", cap: " << v.capacity() << "\n";
	v.resize(11);
	std::cout << "size: " << v.size() << ", cap: " << v.capacity() << "\n";
	return (0);
}