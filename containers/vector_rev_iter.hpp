#ifndef VECTOR_REV_ITER_H
# define VECTOR_REV_ITER_H

# include <iterator> // TO GET iterator_category

# include "vector_iter.hpp"
# include "choose.hpp"

//CIRCULAR DEPENDENCY
template< typename T, bool IsConst >
class	vector_iter;

/*
**	VECTOR REVERSE ITERATOR class DECLARATION
*/

template< typename T, bool IsConst >
class vector_rev_iter
{
public:

	/*
	**	Types for iterator_traits
	**
	**	Including these types is the modern way of writing iterators,
	**	instead of inheriting from std::iterator.
	**	Iterator tags are used by <algorithm> functions to determine the
	**	most efficient algorithm to use.
	*/
	typedef T												value_type;

	/*
	**	SFINAE WILL SELECT THE RIGHT reference AND pointer
	**	BY USING THE choose STRUCTURE
	**
	**	choose IS INCLUDED IN vector_iter.hpp
	*/
	typedef	typename choose<IsConst, const T*, T*>::type	pointer;
	typedef typename choose<IsConst, const T&, T&>::type	reference;

	typedef std::size_t										size_type;
	typedef	ptrdiff_t										difference_type;
	typedef std::random_access_iterator_tag					iterator_category;

	vector_rev_iter<T, IsConst>(void);
	vector_rev_iter<T, IsConst>(pointer v);
	
	/*
	**	SFINAE WILL ONLY ALLOW COPYING FROM A NON-CONST src TO
	**	CONST ITERATOR, AND FROM CONST src TO CONST ITERATOR.
	*/
	template< bool WasConst >
	vector_rev_iter<T, IsConst>(vector_rev_iter<T, WasConst> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);
	
	explicit vector_rev_iter(vector_iter<T, false> const & src);
	
	/*
	**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
	**	FROM const_iterator.
	*/
	vector_rev_iter<T, IsConst> &
		operator=(vector_rev_iter<T, false> const & rhs);

	pointer				base(void) const;
	reference			operator*(void) const;
	vector_rev_iter		operator+(difference_type n) const;
	vector_rev_iter&	operator++(void);
	vector_rev_iter 	operator++(int);
	vector_rev_iter&	operator+=(difference_type n);
	vector_rev_iter 	operator-(difference_type n) const;
	vector_rev_iter& 	operator--(void);
	vector_rev_iter  	operator--(int);
	vector_rev_iter&	operator-=(difference_type n);
	pointer 			operator->(void) const;
	reference 			operator[](difference_type n) const;

	bool
		operator!=(vector_rev_iter<T, IsConst> const & rhs) const;
	bool
		operator==(vector_rev_iter<T, IsConst> const & rhs) const;

private:

	friend class	vector_rev_iter<T, true>;

	pointer	_v;

};

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>::vector_rev_iter(void) : _v(0)
{
	return ;
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>::vector_rev_iter(pointer v) : _v(v)
{
	return ;
}

template< typename T, bool IsConst >
template< bool WasConst >
vector_rev_iter<T, IsConst>::vector_rev_iter(
	vector_rev_iter<T, WasConst> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type *) : _v(src._v)
{
	return ;
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>::vector_rev_iter(vector_iter<T, false> const & src)
	: _v(src._v)
{
	return ;
}

/*
**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
**	FROM const_iterator.
*/
template< typename T, bool IsConst >
vector_rev_iter<T, IsConst> &
	vector_rev_iter<T, IsConst>::operator=(vector_rev_iter<T, false> const & rhs)
{
	this->_v = rhs._v;
	return (*this);
}

template< typename T, bool IsConst >
typename vector_rev_iter<T, IsConst>::pointer
	vector_rev_iter<T, IsConst>::base(void) const
{
	return (this->_v);
}

template< typename T, bool IsConst >
typename vector_rev_iter<T, IsConst>::reference
	vector_rev_iter<T, IsConst>::operator*(void) const
{
	pointer	v(this->_v);

	return (*(--v));
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>
	vector_rev_iter<T, IsConst>::operator+(difference_type n) const
{
	return (this->_v - n);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst> &
	vector_rev_iter<T, IsConst>::operator++(void)
{
	--this->_v;
	return (*this);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>
	vector_rev_iter<T, IsConst>::operator++(int)
{
	vector_rev_iter	prev(*this);

	++(*this);
	return (prev);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst> &
	vector_rev_iter<T, IsConst>::operator+=(difference_type n)
{
	this->_v -= n;
	return (*this);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>
	vector_rev_iter<T, IsConst>::operator-(difference_type n) const
{
	return (this->_v + n);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst> &	vector_rev_iter<T, IsConst>::operator--(void)
{
	++this->_v;
	return (*this);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst>	vector_rev_iter<T, IsConst>::operator--(int)
{
	vector_rev_iter	prev(*this);

	--(*this);
	return (prev);
}

template< typename T, bool IsConst >
vector_rev_iter<T, IsConst> &
	vector_rev_iter<T, IsConst>::operator-=(difference_type n)
{
	this->_v += n;
	return (*this);
}

template< typename T, bool IsConst >
typename vector_rev_iter<T, IsConst>::pointer
	vector_rev_iter<T, IsConst>::operator->(void) const
{
	return (&(this->operator*()));
}

template< typename T, bool IsConst >
typename vector_rev_iter<T, IsConst>::reference
	vector_rev_iter<T, IsConst>::operator[](difference_type n) const
{
	return (this->_v[-n-1]);
}

template< typename T, bool IsConst >
bool
	vector_rev_iter<T, IsConst>::operator!=(
		vector_rev_iter<T, IsConst> const & rhs) const
{
	return (this->_v != rhs._v);
}

template< typename T, bool IsConst >
bool
	vector_rev_iter<T, IsConst>::operator==(
		vector_rev_iter<T, IsConst> const & rhs) const
{
	return (this->_v == rhs._v);
}

// NON-MEMBER functions

template < typename T, bool IsConst >
bool	operator!=(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() != rhs.base());
}

template < typename T, bool IsConst >
bool	operator==(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() == rhs.base());
}

template < typename T, bool IsConst >
bool	operator<(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() > rhs.base());
}

template < typename T, bool IsConst >
bool	operator<=(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() >= rhs.base());
}

template < typename T, bool IsConst >
bool	operator>(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() < rhs.base());
}

template < typename T, bool IsConst >
bool	operator>=(vector_rev_iter<T, IsConst> const & lhs,
	vector_rev_iter<T, IsConst> const & rhs)
{
	return (lhs.base() <= rhs.base());
}

template < typename T, bool IsConst >
vector_rev_iter<T, IsConst>
	operator+(typename vector_rev_iter<T, IsConst>::difference_type n,
	vector_rev_iter<T, IsConst> const & rev_it)
{
	return (rev_it + n);
}

template < typename T, bool IsConst >
typename vector_rev_iter<T, IsConst>::difference_type
	operator-(const vector_rev_iter<T, IsConst>& lhs,
	const vector_rev_iter<T, IsConst>& rhs)
{
	return (rhs.base() - lhs.base());
}

#endif