#ifndef VECTOR_ITER_H
# define VECTOR_ITER_H

# include "../type_traits/type_traits.hpp"
# include "vector_rev_iter.hpp"
# include "choose.hpp"

/*
**	vector ITERATOR CLASS DECLARATION
*/

template< typename T, bool IsConst >
class vector_iter
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
	typedef T								value_type;

	/*
	**	SFINAE WILL SELECT THE RIGHT reference AND pointer
	**	BY USING THE choose STRUCTURE
	*/
	typedef	typename choose<IsConst, const T*, T*>::type	pointer;
	typedef typename choose<IsConst, const T&, T&>::type	reference;

	typedef std::size_t						size_type;
	typedef	ptrdiff_t						difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

	//Default constructor
	vector_iter<T, IsConst>(void);
	vector_iter<T, IsConst>(pointer v);

	/*
	**	SFINAE WILL ONLY ALLOW COPYING FROM A NON-CONST src TO
	**	CONST ITERATOR, AND FROM CONST src TO CONST ITERATOR.
	*/
	template<bool WasConst>
	vector_iter<T, IsConst>(vector_iter<T, WasConst> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);
	
	~vector_iter(void);

	/*
	**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
	**	FROM const_iterator.
	*/
	vector_iter<T, IsConst> &	operator=(vector_iter<T, false> const & rhs);

	bool						operator!=(vector_iter<T, IsConst> const & rhs) const;
	bool						operator==(vector_iter<T, IsConst> const & rhs) const;
	reference					operator*(void) const;
	pointer						operator->(void) const;
	vector_iter<T, IsConst> &	operator++(void);
	vector_iter<T, IsConst>		operator++(int);
	vector_iter<T, IsConst> &	operator--(void);
	vector_iter<T, IsConst>		operator--(int);
	vector_iter<T, IsConst>		operator+(difference_type offset) const;
	difference_type				operator+(vector_iter<T, IsConst> const & rhs) const;
	vector_iter<T, IsConst>		operator-(difference_type offset) const;
	difference_type				operator-(vector_iter<T, IsConst> const & rhs) const;
	bool						operator<(vector_iter<T, IsConst> const & rhs) const;
	bool						operator>(vector_iter<T, IsConst> const & rhs) const;
	bool						operator<=(vector_iter<T, IsConst> const & rhs) const;
	bool						operator>=(vector_iter<T, IsConst> const & rhs) const;
	vector_iter<T, IsConst> &	operator+=(difference_type offset);
	vector_iter<T, IsConst> &	operator-=(difference_type offset);
	reference					operator[](difference_type offset) const;

private:

	//In order to access private members of const from non const.
	friend class	vector_iter<T, true>;

	/*
	**	vector_rev_iter FRIENDSHIP IS NEEDED TO ELUDE THE CREATION
	**	OF PUBLIC GETTERS, WHICH ARE NOT PRESENT IN STANDARD ITERATORS.
	**
	**	Adding explicitly both specializations of IsConst, because IsConst
	**	is either true or false in this instance, and need interaction with
	**	both. IsConst is no longer an undefined variable inside this instance,
	**	that is why it needs to be defined explicitly to include both versions.	
	*/
	friend class	vector_rev_iter<T, true>;
	friend class	vector_rev_iter<T, false>;

	pointer	_v;

};

template< typename T, bool IsConst >
vector_iter<T, IsConst>::vector_iter(void) : _v(0)
{
	return ;
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>::vector_iter(pointer v) : _v(v)
{
	return ;
}

template< typename T, bool IsConst >
template< bool WasConst >
vector_iter<T, IsConst>::vector_iter(vector_iter<T, WasConst> const & src,
	typename ft::enable_if<IsConst || !WasConst>::type *) : _v(0)
{
	*this = src;
	return ;
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>::~vector_iter(void)
{
	return ;
}

/*
**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
**	FROM const_iterator.
*/
template< typename T, bool IsConst >
vector_iter<T, IsConst> &
	vector_iter<T, IsConst>::operator=(vector_iter<T, false> const & rhs)
{
	this->_v = rhs._v;
	return (*this);
}

template< typename T, bool IsConst >
bool	vector_iter<T, IsConst>::operator!=(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v != rhs._v);
}

template< typename T, bool IsConst >
bool	vector_iter<T, IsConst>::operator==(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v == rhs._v);
}

/*
**	We do not have access to the inner vector array, instead,
**	we have access to the vector interface which provides
**	operator[] and at() to access elements by index.
*/
template< typename T, bool IsConst >
typename vector_iter<T, IsConst>::reference
	vector_iter<T, IsConst>::operator*(void) const
{
	return (*(this->_v));
}

template< typename T, bool IsConst >
typename vector_iter<T, IsConst>::pointer
	vector_iter<T, IsConst>::operator->(void) const
{
	return (this->_v);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst> &	vector_iter<T, IsConst>::operator++(void)
{
	this->_v += 1;
	return (*this);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>	vector_iter<T, IsConst>::operator++(int)
{
	vector_iter<T, IsConst>	prev(*this);

	this->_v += 1;
	return (prev);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst> &	vector_iter<T, IsConst>::operator--(void)
{
	this->_v -= 1;
	return (*this);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>	vector_iter<T, IsConst>::operator--(int)
{
	vector_iter<T, IsConst>	prev(*this);

	this->_v -= 1;
	return (prev);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>
	vector_iter<T, IsConst>::operator+(difference_type offset) const
{
	vector_iter<T, IsConst>	res(this->_v + offset);

	return (res);
}

template< typename T, bool IsConst >
typename vector_iter<T, IsConst>::difference_type
	vector_iter<T, IsConst>::operator+(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v + rhs._v);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>
	vector_iter<T, IsConst>::operator-(difference_type offset) const
{
	vector_iter<T, IsConst>	res(this->_v - offset);

	return (res);
}

template< typename T, bool IsConst >
typename vector_iter<T, IsConst>::difference_type
	vector_iter<T, IsConst>::operator-(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v - rhs._v);
}

template< typename T, bool IsConst >
bool
	vector_iter<T, IsConst>::operator<(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v < rhs._v);
}

template< typename T, bool IsConst >
bool
	vector_iter<T, IsConst>::operator>(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v > rhs._v);
}

template< typename T, bool IsConst >
bool
	vector_iter<T, IsConst>::operator<=(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v <= rhs._v);
}

template< typename T, bool IsConst >
bool
	vector_iter<T, IsConst>::operator>=(vector_iter<T, IsConst> const & rhs) const
{
	return (this->_v >= rhs._v);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst> &
	vector_iter<T, IsConst>::operator+=(difference_type offset)
{
	this->_v += offset;
	return (*this);
}

template< typename T, bool IsConst >
vector_iter<T, IsConst> &
vector_iter<T, IsConst>::operator-=(difference_type offset)
{
	this->_v -= offset;
	return (*this);
}

template< typename T, bool IsConst >
typename vector_iter<T, IsConst>::reference
	vector_iter<T, IsConst>::operator[](difference_type offset) const
{
	return (*(this->_v + offset));
}

template< typename T, bool IsConst >
vector_iter<T, IsConst>
	operator+(typename vector_iter<T, IsConst>::difference_type offset,
		vector_iter<T, IsConst> const & rhs)
{
	return (rhs + offset);
}

#endif