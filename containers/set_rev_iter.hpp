#ifndef SET_REV_ITER_H
# define SET_REV_ITER_H

# include <memory>
# include <functional> // FOR std::less

# include "../utility/utility.hpp"
# include "../type_traits/type_traits.hpp"
# include "TreeNode.hpp"
# include "set_iter.hpp"

/*
**	SET REVERSE ITERATOR class DECLARATION
*/

template< typename T, typename Compare = std::less< T >,
	typename Alloc = std::allocator< T > >
class set_rev_iter
{
public:

	/*
	**	Types for iterator_traits
	*/
	typedef T											key_type;
	typedef	T											value_type;
	typedef	Compare										key_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::pointer			pointer;	
	typedef std::size_t									size_type;
	typedef	ptrdiff_t									difference_type;
	typedef std::bidirectional_iterator_tag				iterator_category;

	// TO REUSE THE FUNCTIONALITY OF set_iter IN SOME FUNCTIONS
	typedef set_iter<T, Compare, Alloc>					iter;

	typedef TreeNode< value_type >						node;

	set_rev_iter(void);
	explicit set_rev_iter(node * n, size_type end_offset = 0,
		size_type begin_offset = 0);

	set_rev_iter(set_rev_iter const & src);	
	explicit set_rev_iter(set_iter<T, Compare, Alloc> const & src);

	set_rev_iter &	operator=(set_rev_iter const & rhs);

	set_rev_iter	base(void) const;
	const_reference	operator*(void) const;
	const_pointer	operator->(void) const;
	set_rev_iter &	operator++(void);
	set_rev_iter 	operator++(int);
	set_rev_iter & 	operator--(void);
	set_rev_iter  	operator--(int);
	bool			operator!=(set_rev_iter const & rhs) const;
	bool			operator==(set_rev_iter const & rhs) const;

private:

	key_compare	_comp;
	node *		_node;
	size_type	_end_offset;
	size_type	_begin_offset;

};

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>::set_rev_iter(void)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>::set_rev_iter(node * n,
	size_type end_offset, size_type begin_offset)
	: _comp(key_compare()), _node(n), _end_offset(end_offset),
	_begin_offset(begin_offset)
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>::set_rev_iter(set_rev_iter const & src)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	*this = src;
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>::set_rev_iter(
	set_iter<T, Compare, Alloc> const & src) : _comp(key_compare()),
		_node(src.getNode()), _end_offset(src.getEndOffset()),
		_begin_offset(src.getBeginOffset())
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc> &
	set_rev_iter<T, Compare, Alloc>::operator=(set_rev_iter const & rhs)
{
	/*
	**	NO DEEP COPY NECESSARY BECAUSE THEY ARE ITERATORS THAT ITERATE
	**	OVER THE SAME MAP.
	*/
	this->_comp = rhs._comp;
	this->_node = rhs._node;
	this->_end_offset = rhs._end_offset;
	this->_begin_offset = rhs._begin_offset;
	return (*this);
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>
	set_rev_iter<T, Compare, Alloc>::base(void) const
{
	return (*this);
}

template< typename T, typename Compare, typename Alloc >
typename set_rev_iter<T, Compare, Alloc>::const_reference
	set_rev_iter<T, Compare, Alloc>::operator*(void) const
{
	//THIS IS THE set_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	return (*(--it));
}

template< typename T, typename Compare, typename Alloc >
typename set_rev_iter<T, Compare, Alloc>::const_pointer
	set_rev_iter<T, Compare, Alloc>::operator->(void) const
{
	return (&(this->operator*()));
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc> &
	set_rev_iter<T, Compare, Alloc>::operator++(void)
{
	//THIS IS THE set_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	--it;
	this->_node = it.getNode();
	this->_end_offset = it.getEndOffset();
	this->_begin_offset = it.getBeginOffset();
	return (*this);
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>
	set_rev_iter<T, Compare, Alloc>::operator++(int)
{
	set_rev_iter	prev(*this);

	++(*this);
	return (prev);
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc> &
	set_rev_iter<T, Compare, Alloc>::operator--(void)
{
	//THIS IS THE set_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	++it;
	this->_node = it.getNode();
	this->_end_offset = it.getEndOffset();
	this->_begin_offset = it.getBeginOffset();
	return (*this);
}

template< typename T, typename Compare, typename Alloc >
set_rev_iter<T, Compare, Alloc>
	set_rev_iter<T, Compare, Alloc>::operator--(int)
{
	set_rev_iter	prev(*this);

	--(*this);
	return (prev);
}

template< typename T, typename Compare, typename Alloc >
bool
	set_rev_iter<T, Compare, Alloc>::operator!=(set_rev_iter const & rhs) const
{
	return (this->_node != rhs._node
		|| this->_begin_offset != rhs._begin_offset
		|| this->_end_offset != rhs._end_offset);
}

template< typename T, typename Compare, typename Alloc >
bool
	set_rev_iter<T, Compare, Alloc>::operator==(set_rev_iter const & rhs) const
{
	return (!(*this != rhs));
}

#endif