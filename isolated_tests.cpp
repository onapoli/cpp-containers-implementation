#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "containers/vector.hpp"

#include <unistd.h>

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

void	resize()
{
	{
		time_t start, end, diff;
		/*
			* test with n greater than vector capacity
			*/
		/*------------------ std::vectors ---------------------*/
		std::vector<std::string> v1(10, "string2");
		start = get_time();
		v1.resize(1e6);
		end = get_time();
		diff = end - start;
		diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		/*------------------ ft::vectors ---------------------*/
		ft::vector<std::string> ft_v1(10, "string2");
		ualarm(diff * 1e3, 0);
		ft_v1.resize(1e6);
		ualarm(0, 0);
		/*----------------------------------------------------*/
		/*
			*	test with n lesser than capacity and greater than size
			*/
		/*------------------ std::vectors ---------------------*/
		v1.resize(20);
		start = get_time();
		v1.resize(1e5);
		end = get_time();
		diff = end - start;
		diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		/*------------------ ft::vectors ---------------------*/
		ft_v1.resize(20);
		ualarm(diff * 1e3, 0);
		ft_v1.resize(1e5);
		ualarm(0, 0);
		/*----------------------------------------------------*/
		/*
			* test with n lesser than capacity and lesser an size
			*/
		/*------------------ std::vectors ---------------------*/
		v1.resize(100);
		start = get_time();
		v1.resize(50);
		end = get_time();
		diff = end - start;
		diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		/*------------------ ft::vectors ---------------------*/
		ft_v1.resize(100);
		ualarm(diff * 1e3, 0);
		ft_v1.resize(50);
		ualarm(0, 0);
		/*----------------------------------------------------*/
	}
	/*
	* Strings to store the results
	*/
	std::string s1, s2, s3, s4, ft_s1, ft_s2, ft_s3, ft_s4;
	std::string sit1, sit2, sit3, ft_sit1, ft_sit2, ft_sit3; // strings to store the result by iterators
	/*
	* Var to store the size and the capacity
	*/
	size_t z1, z2, z3, z4, ft_z1, ft_z2, ft_z3, ft_z4;
	size_t c1, c2, c3, c4, ft_c1, ft_c2, ft_c3, ft_c4;
	/*
	* iterators to check the iterator validity
	*  it : iterator, eit : iterator to the end
	*/
	std::vector<std::string>::iterator valid_it, valid_eit;
	ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
	/*
	* test with n greater than vector capacity
	*/
	/*------------------ std::vectors ---------------------*/
	std::vector<std::string> v1(10, "string2");
	v1.resize(1e6, "hello");
	/*------------------ ft::vectors ---------------------*/
	ft::vector<std::string> ft_v1(10, "string2");
	ft_v1.resize(1e6, "hello");

	z1 = v1.size();
	ft_z1 = ft_v1.size();
	c1 = v1.capacity();
	ft_c1 = ft_v1.capacity();
	for (size_t i = 0; i < v1.size(); ++i)
		s1 += v1[i];

	for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
		ft_s1 += *it;
	/*----------------------------------------------------*/
	/*
	*	test with n lesser than capacity and greater than size
	*/
	/*------------------ std::vectors ---------------------*/
	v1.resize(20);

	std::cout << "resize to 20" << std::endl;
	std::cout << "v1.size(): " << v1.size() << " v1.capacity(): " << v1.capacity() << std::endl;

	valid_it = v1.begin();
	valid_eit = v1.end();
	v1.resize(1e5);

	std::cout << "resize to 1e5" << std::endl;
	std::cout << "v1.size(): " << v1.size() << " v1.capacity(): " << v1.capacity() << std::endl;

	/*------------------ ft::vectors ---------------------*/
	ft_v1.resize(20);

	std::cout << "\nresize to 20" << std::endl;
	std::cout << "ft_v1.size(): " << ft_v1.size() << " ft_v1.capacity(): " << ft_v1.capacity() << std::endl;

	ft_valid_it = ft_v1.begin();
	ft_valid_eit = ft_v1.end();
	ft_v1.resize(1e5);

	std::cout << "resize to 1e5" << std::endl;
	std::cout << "ft_v1.size(): " << ft_v1.size() << " ft_v1.capacity(): " << ft_v1.capacity() << std::endl;

	z2 = v1.size();
	ft_z2 = ft_v1.size();
	c2 = v1.capacity();
	ft_c2 = ft_v1.capacity();
	for (size_t i = 0; i < v1.size(); ++i)
		s2 += v1[i];

	for (; valid_it != valid_eit; ++valid_it)
	{
		sit1 += *valid_it;
	}

	for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
		ft_s2 += *it;

	/*for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
	{
		ft_sit1 += *ft_valid_it;
	}*/
	/*----------------------------------------------------*/
	/*
	* test with n lesser than capacity and lesser an size
	*/
	/*------------------ std::vectors ---------------------*/
	valid_it = v1.begin();
	v1.resize(50);
	/*------------------ ft::vectors ---------------------*/
	ft_valid_it = ft_v1.begin();
	ft_v1.resize(50);

	z3 = v1.size();
	ft_z3 = ft_v1.size();
	c3 = v1.capacity();
	ft_c3 = ft_v1.capacity();
	for (size_t i = 0; i < v1.size(); ++i)
		s3 += v1[i];

	for (; valid_it != v1.end(); ++valid_it)
		sit2 += *valid_it;

	for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
		ft_s3 += *it;

	/*for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
		ft_sit2 += *ft_valid_it;*/
	/*----------------------------------------------------*/
	/*
		* test with n = 0
		*/
	/*------------------ std::vectors ---------------------*/
	valid_it = v1.begin();
	v1.resize(0, "string4");
	/*------------------ ft::vectors ---------------------*/
	ft_valid_it = ft_v1.begin();
	ft_v1.resize(0, "string4");

	z4 = v1.size();
	ft_z4 = ft_v1.size();
	c4 = v1.capacity();
	ft_c4 = ft_v1.capacity();
	for (size_t i = 0; i < v1.size(); ++i)
		s4 += v1[i];

	for (; valid_it != v1.end(); ++valid_it)
		sit3 += *valid_it;

	for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
		ft_s4 += *it;

	/*for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
		ft_sit3 += *ft_valid_it;*/
	/*----------------------------------------------------*/
	EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3 && sit2 == ft_sit2) && (s4 == ft_s4 && z4 == ft_z4 && c4 == ft_c4 && sit3 == ft_sit3));
}

void	assign_fill()
{
	/*------------------ std::vectors ---------------------*/
	std::vector<std::string> v1(10, "string2");
	std::vector<char> v2;
	/*------------------ std::vectors ---------------------*/
	ft::vector<std::string> ft_v1(10, "string2");
	ft::vector<char> ft_v2;
	/*
		* Strings to store the results
		*/
	std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
	/*
		* Var to store the size and the capacity
		*/
	size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
	size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
	// test for n greater than the vector capactiy
	v1.assign(20, "assign");
	ft_v1.assign(20, "assign");

	z1 = v1.size();
	ft_z1 = ft_v1.size();
	c1 = v1.capacity();
	ft_c1 = ft_v1.capacity();
	for (size_t i = 0; i < v1.size(); ++i)
		s1 += v1.at(i);

	for (size_t i = 0; i < ft_v1.size(); ++i)
		ft_s1 += ft_v1.at(i);
	// test for n lesser than the vector capactiy
	v1.assign(10, "less");
	ft_v1.assign(10, "less");

	z2 = v1.size();
	ft_z2 = ft_v1.size();
	c2 = v1.capacity();

	std::cout << "c2: " << c2 << std::endl;

	ft_c2 = ft_v1.capacity();

	std::cout << "ft_c2: " << ft_c2 << std::endl;

	for (size_t i = 0; i < v1.size(); ++i)
		s3 += v1.at(i);

	for (size_t i = 0; i < ft_v1.size(); ++i)
		ft_s3 += ft_v1.at(i);
	// test for empty vectors
	v2.assign(20, 'h');
	ft_v2.assign(20, 'h');

	z3 = v2.size();
	ft_z3 = ft_v2.size();
	c3 = v2.capacity();
	ft_c3 = ft_v2.capacity();
	for (size_t i = 0; i < v2.size(); ++i)
		s2 += v2.at(i);

	for (size_t i = 0; i < ft_v2.size(); ++i)
		ft_s2 += ft_v2.at(i);

	EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
}

void	push_back()
{
	/*------------------ std::vectors ---------------------*/
	std::vector<std::string> v;
	/*------------------ std::vectors ---------------------*/
	ft::vector<std::string> ft_v;
	/*
		* Strings to store the results
		*/
	std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
	/*
		* Var to store the size and the capacity
		*/
	size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
	size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
	ft::vector<std::string>::iterator ft_it;
	// test for an empty vector
	v.push_back("hello");
	ft_v.push_back("hello");
	ft_it = ft_v.begin();
	ft_it->length();

	z1 = v.size();
	c1 = v.capacity();
	ft_z1 = ft_v.size();
	ft_c1 = ft_v.capacity();
	for (size_t i = 0; i < v.size(); ++i)
		s1 += v.at(i);

	for (size_t i = 0; i < ft_v.size(); ++i)
		ft_s1 += ft_v.at(i);
	/*---------------------------------------------*/
	// test for a vector with capacity >= size + the new element
	v.reserve(30);
	ft_v.reserve(30);
	v.push_back("string");
	ft_v.push_back("string");
	v.push_back("string");
	ft_v.push_back("string");

	z2 = v.size();
	c2 = v.capacity();
	ft_z2 = ft_v.size();
	ft_c2 = ft_v.capacity();
	for (size_t i = 0; i < v.size(); ++i)
		s2 += v.at(i);

	for (size_t i = 0; i < ft_v.size(); ++i)
		ft_s2 += ft_v.at(i);
	/*---------------------------------------------------------*/
	// test for a vector with capactiy < size + the new element
	for (size_t i = 0; i < 100; ++i)
		v.push_back("string");

	for (size_t i = 0; i < 100; ++i)
		ft_v.push_back("string");

	z3 = v.size();
	c3 = v.capacity();
	ft_z3 = ft_v.size();
	ft_c3 = ft_v.capacity();
	for (size_t i = 0; i < v.size(); ++i)
		s3 += v.at(i);

	for (size_t i = 0; i < ft_v.size(); ++i)
		ft_s3 += ft_v.at(i);

	std::cout << "s1: " << s1 << " z1: " << z1 << " c1 " << c1 << std::endl;
	std::cout << "ft_s1: " << ft_s1 << " ft_z1: " << ft_z1 << " ft_c1 " << ft_c1 << std::endl;
	EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
}

void	clear()
{
	/*
		* strings to store the resutls
		*/
	std::string str, ft_str;
	/*
		* var to store the size and the capacity
		*/
	ft::vector<std::string>::size_type s, ft_s;
	ft::vector<std::string>::size_type c, ft_c;
	/*
		* bool to store the comparison
		*/
	bool cond;

	/*---------------------------------- test 1: equal size vectors ----------------------*/
	{
		std::vector<std::string> v(200, "hello");
		ft::vector<std::string> ft_v(200, "hello");

		v.clear();
		ft_v.clear();

		s = v.size();
		ft_s = ft_v.size();
		c = v.capacity();
		ft_c = ft_v.capacity();
		for (size_t i = 0; i < v.size(); ++i)
			str += v[i];
		for (size_t i = 0; i < ft_v.size(); ++i)
			ft_str += ft_v[i];
		
		std::cout << "v.capacity() " << c << " ft_v.capacity() " << ft_c << std::endl;
		cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
	}
	/*--------------------------------------------------------------------------------------------*/
	EQUAL(cond);
}

void	reserve()
{
	/*-------------------------------------- time limit test -----------------------------------*/
	{
		time_t start, end, diff;
		/*------------------ std::vectors ---------------------*/
		std::vector<std::string> v1(10, "string2");
		start = get_time();
		v1.reserve(1e6);
		end = get_time();
		diff = end - start;
		diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
		/*------------------ ft::vectors ---------------------*/
		ft::vector<std::string> ft_v1(10, "string2");
		ualarm(diff * 1e3, 0);
		ft_v1.reserve(1e6);
		ualarm(0, 0);
	}
	/*
		* Strings to store the results
		*/
	std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
	std::string sit1, ft_sit1; // strings to store the result by iterators
	/*
		* Var to store the size and the capacity
		*/
	size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
	size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
	/*
		* iterators to check the iterator validity
		*  it : iterator, eit : iterator to the end
		*/
	std::vector<std::string>::iterator valid_it, valid_eit;
	ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
	// bool to check if the function throw or not
	bool exec_throwed = false;
	/*------------------ std::vectors ---------------------*/
	std::vector<std::string> v1(10, "string2");
	std::vector<char> v2;
	/*------------------ std::vectors ---------------------*/
	ft::vector<std::string> ft_v1(10, "string2");
	ft::vector<char> ft_v2;
	/*try
	{
		ft_v1.reserve(ft_v1.max_size() + 1);
	}
	catch (std::length_error const &e)
	{
		(void)e;
		exec_throwed = true;
	}*/
	v1.reserve(100);
	ft_v1.reserve(100);

	z1 = v1.size();
	ft_z1 = ft_v1.size();
	c1 = v1.capacity();
	ft_c1 = ft_v1.capacity();

	for (size_t i = 0; i < v1.size(); ++i)
		s1 += v1[i];

	ft_valid_it = ft_v1.begin();
	/*for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
		ft_s1 += *ft_valid_it;*/

	valid_it = v1.begin();
	valid_eit = v1.end();
	ft_valid_it = ft_v1.begin();
	ft_valid_eit = ft_v1.end();
	v1.reserve(50);
	ft_v1.reserve(50);

	z2 = v1.size();
	ft_z2 = ft_v1.size();
	c2 = v1.capacity();
	ft_c2 = ft_v1.capacity();

	for (size_t i = 0; i < v1.size(); ++i)
		s2 += v1[i];

	for (; valid_it != valid_eit; ++valid_it)
		sit1 += *valid_it;

	/*for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
		ft_s2 += *it;*/

	/*for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
		ft_sit1 += *ft_valid_it;*/

	v2.reserve(200);
	ft_v2.reserve(200);
	z3 = v2.size();
	ft_z3 = ft_v2.size();
	c3 = v2.capacity();
	ft_c3 = ft_v2.capacity();

	for (size_t i = 0; i < v2.size(); ++i)
		s3 += v2[i];

	/*for (ft::vector<char>::iterator it = ft_v2.begin(); it != ft_v2.end(); ++it)
		ft_s3 += *it;*/

	EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3) && exec_throwed);
}

void	insert_range()
{
	/*
		* strings to store the resutls
		*/
	std::string str, ft_str;
	/*
		* var to store the size and the capacity
		*/
	ft::vector<std::string>::size_type s, ft_s;
	ft::vector<std::string>::size_type c, ft_c;
	/*
		* bool to store the comparison
		*/
	bool cond;
	
	std::vector<std::string> v1(70, "hello");
	std::vector<std::string> v(20, "string");
	ft::vector<std::string> ft_v(20, "string");
	ft::vector<std::string>::iterator valid_it;

	v.reserve(100);
	ft_v.reserve(100);
	valid_it = ft_v.begin();
	v.insert(v.begin() + 15, v1.begin(), v1.end());
	ft_v.insert(ft_v.begin() + 15, v1.begin(), v1.end());

	str.clear();
	ft_str.clear();
	s = v.size();
	ft_s = ft_v.size();
	c = v.capacity();
	ft_c = ft_v.capacity();
	for (size_t i = 0; i < v.size(); ++i)
		str += v[i];
	for (size_t i = 0; i < ft_v.size(); ++i)
		ft_str += ft_v[i];
	cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
}

void	erase()
{
	std::vector<std::string>::iterator it;
    ft::vector<std::string>::iterator ft_it;
	
	std::vector<std::string> v(100, "hello");
	ft::vector<std::string> ft_v(100, "hello");

	it = v.erase(v.begin(), v.end());
	ft_it = ft_v.erase(ft_v.begin(), ft_v.end());
}

void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}

int	main(void)
{
	signal(SIGALRM, alarm_handler);

	resize();
	reserve();
	assign_fill();
	push_back();
	clear();
	insert_range();
	erase();
	return (0);
}