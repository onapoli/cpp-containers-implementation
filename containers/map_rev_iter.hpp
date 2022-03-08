#ifndef MAP_REV_ITER_H
# define MAP_REV_ITER_H

# include <memory>
# include <functional> // FOR std::less

# include "../utility/utility.hpp"
# include "../type_traits/type_traits.hpp"
# include "TreeNode.hpp"
# include "map_iter.hpp"

/*
**	MAP REVERSE ITERATOR class DECLARATION
*/

template< typename Key, typename T, bool IsConst,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator< ft::pair<Key const, T> > >
class map_rev_iter
{
public:

	/*
	**	Types for iterator_traits
	*/
	typedef Key										key_type;
	typedef	T										mapped_type;
	typedef	ft::pair< key_type const, mapped_type >	value_type;
	typedef	Compare									key_compare;
	typedef Alloc									allocator_type;
	
	/*
	**	SFINAE WILL SELECT THE RIGHT reference AND pointer
	**	BY USING THE choose STRUCTURE
	**
	**	choose IS ALREADY INCLUDED IN map_iter.hpp, SO IT IS NOT
	**	NECESSARY TO INCLUDE IT IN THIS FILE.
	*/
	typedef typename choose<IsConst,
		typename allocator_type::const_reference,
		typename allocator_type::reference>::type	reference;
	typedef typename choose<IsConst,
		typename allocator_type::const_pointer,
		typename allocator_type::pointer>::type		pointer;
	
	typedef std::size_t								size_type;
	typedef	ptrdiff_t								difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;

	// TO REUSE THE FUNCTIONALITY OF map_iter IN SOME FUNCTIONS
	typedef map_iter<Key, T, IsConst, Compare, Alloc>	iter;

	typedef TreeNode<Key, T>						node;

	map_rev_iter(void);
	explicit map_rev_iter(node * n, size_type end_offset = 0,
		size_type begin_offset = 0);

	/*
	**	SFINAE WILL ONLY ALLOW COPYING FROM A NON-CONST rev_it TO
	**	CONST rev_it, AND FROM CONST rev_it TO CONST rev_it.
	*/
	template< bool WasConst >
	map_rev_iter(map_rev_iter<Key, T, WasConst, Compare, Alloc> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);
	
	/*
	**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
	**	FROM const_iterator.
	*/
	map_rev_iter &
		operator=(map_rev_iter<Key, T, false, Compare, Alloc> const & rhs);

	map_rev_iter	base(void) const;
	reference		operator*(void) const;
	map_rev_iter &	operator++(void);
	map_rev_iter 	operator++(int);
	map_rev_iter & 	operator--(void);
	map_rev_iter  	operator--(int);
	pointer 		operator->(void) const;
	bool			operator!=(map_rev_iter const & rhs) const;
	bool			operator==(map_rev_iter const & rhs) const;

private:

	//In order to access private members of const from non const.
	friend class	map_rev_iter<Key, T, true, Compare, Alloc>;

	key_compare	_comp;
	node *		_node;
	size_type	_end_offset;
	size_type	_begin_offset;

};

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc>::map_rev_iter(void)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	return ;
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc>::map_rev_iter(node * n,
	size_type end_offset, size_type begin_offset)
	: _comp(key_compare()), _node(n), _end_offset(end_offset),
	_begin_offset(begin_offset)
{
	return ;
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
template< bool WasConst >
map_rev_iter<Key, T, IsConst, Compare, Alloc>::map_rev_iter(
	map_rev_iter<Key, T, WasConst, Compare, Alloc> const & src,
	typename ft::enable_if<IsConst || !WasConst>::type *)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	*this = src;
	return ;
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc> &
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator=(
		map_rev_iter<Key, T, false, Compare, Alloc> const & rhs)
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

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc>
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::base(void) const
{
	return (*this);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
typename map_rev_iter<Key, T, IsConst, Compare, Alloc>::reference
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator*(void) const
{
	//THIS IS THE map_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	return (*(--it));
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc> &
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator++(void)
{
	//THIS IS THE map_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	--it;
	this->_node = it.getNode();
	this->_end_offset = it.getEndOffset();
	this->_begin_offset = it.getBeginOffset();
	return (*this);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc>
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator++(int)
{
	map_rev_iter	prev(*this);

	++(*this);
	return (prev);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc> &
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator--(void)
{
	//THIS IS THE map_iter CLASS iterator, TO AVOID CODE DUPLICATION
	iter	it(this->_node, this->_end_offset, this->_begin_offset);

	++it;
	this->_node = it.getNode();
	this->_end_offset = it.getEndOffset();
	this->_begin_offset = it.getBeginOffset();
	return (*this);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
map_rev_iter<Key, T, IsConst, Compare, Alloc>
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator--(int)
{
	map_rev_iter	prev(*this);

	--(*this);
	return (prev);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
typename map_rev_iter<Key, T, IsConst, Compare, Alloc>::pointer
	map_rev_iter<Key, T, IsConst, Compare, Alloc>::operator->(void) const
{
	return (&(this->operator*()));
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
bool
	map_rev_iter<Key, T, IsConst,
		Compare, Alloc>::operator!=(map_rev_iter const & rhs) const
{
	return (this->_node != rhs._node
		|| this->_begin_offset != rhs._begin_offset
		|| this->_end_offset != rhs._end_offset);
}

template< typename Key, typename T, bool IsConst, typename Compare,
	typename Alloc >
bool
	map_rev_iter<Key, T, IsConst,
		Compare, Alloc>::operator==(map_rev_iter const & rhs) const
{
	return (!(*this != rhs));
}

#endif