#include <iostream>

#include "type_traits/type_traits.hpp"

template<bool IsConst>
class MyIterator {

	friend class	MyIterator<true>;
	//friend class	MyIterator<false>;
    int	_d;

public:

	MyIterator(void) : _d(1) {};
	MyIterator(MyIterator<IsConst> const & src) : _d(2)
	{
		(void)src;
	};

	template<bool WasConst>
    MyIterator(MyIterator<WasConst> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0) : _d(2)
	{
		(void)src;
	};

	~MyIterator(void) {};

	/*MyIterator<IsConst> &	operator=(MyIterator<IsConst> const & rhs)
	{
		if (this != &rhs)
			this->_d = rhs._d;
		return (*this);
	};*/

	MyIterator<IsConst> &	operator=(MyIterator<false> const & rhs)
	{
		this->_d = rhs._d;
		return (*this);
	};
	
	bool					operator!=(MyIterator<IsConst> const& rhs)
	{
		return (this->_d != rhs._d);
	};

	bool					operator==(MyIterator<IsConst> const& rhs)
	{
		return (!(this->_d != rhs._d));
	};

	int						getD(void) const
	{
		return (this->_d);
	};
};

int	main(void)
{
	MyIterator<false>	it;
	MyIterator<true>	cit(it);

	std::cout << cit.getD() << std::endl;
	cit = it;
	std::cout << cit.getD() << std::endl;
	if (it == it)
		std::cout << "yeah" << std::endl;
	return (0);
}