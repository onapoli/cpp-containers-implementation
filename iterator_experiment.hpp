#ifndef ITERATOR_EXPERIMENT_H
# define ITERATOR_EXPERIMENT_H

# include "type_traits/type_traits.hpp"

template<bool IsConst>
class MyIterator {

	friend class	MyIterator<true>;

    int	_i;

public:

	MyIterator(void);
	MyIterator(MyIterator<IsConst> const & src);

	template<bool WasConst>
    MyIterator(MyIterator<WasConst> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);
	
	~MyIterator(void);

	MyIterator<IsConst> &	operator=(MyIterator<false> const & rhs);
	
	bool					operator==(MyIterator const& rhs);
};

template<bool IsConst>
MyIterator<IsConst>::MyIterator(void) : _i(0)
{}

template<bool IsConst>
MyIterator<IsConst>::MyIterator(MyIterator<IsConst> const & src) : _i(src._i)
{}

template<bool IsConst>
template<bool WasConst>
MyIterator<IsConst>::MyIterator(MyIterator<WasConst> const & src,
	typename ft::enable_if<IsConst || !WasConst>::type *) : _i(src._i)
{}

template<bool IsConst>
MyIterator<IsConst> &	MyIterator<IsConst>::operator=(MyIterator<false> const & rhs)
{
	this->_i = rhs._i;
	return (*this);
}

#endif
