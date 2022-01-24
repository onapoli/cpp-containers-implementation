#include <iostream>

#include "type_traits/type_traits.hpp"

// The second function argument is only valid if T is an integral type:
template < typename T >
bool is_even (T i, typename
	ft::enable_if<ft::is_integral<T>::value>::type * = 0)
{
	return (!bool(i % 2));
}

void	is_integral_test(void)
{
	std::cout << "\n\n--- IS INTEGRAL TESTS ---\n";
	std::cout << std::boolalpha;
	std::cout << "\nint is integral? " << ft::is_integral<int>::value;
	std::cout << "\nchar is integral? " << ft::is_integral<char>::value;
	std::cout << "\nfloat is integral? " << ft::is_integral<float>::value;
	std::cout << "\nint * is integral? " << ft::is_integral<int *>::value;
	std::cout << std::endl;
	return ;
}

void	enable_if_test(void)
{
	std::cout << "\n\n--- ENABLE_IF TESTS ---\n";
	short int i = 1;    // code does not compile if type of i is not integral

	std::cout << std::boolalpha;
	std::cout << "short int i = 1\n";
	std::cout << "i is even: " << is_even(i) << "\n";
	std::cout << "2 is even: " << is_even(2) << std::endl;
	return ;
}

int	main(void)
{
	is_integral_test();
	enable_if_test();
	return (0);
}