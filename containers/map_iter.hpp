#ifndef MAP_ITER_H
# define MAP_ITER_H

# include <cstddef> // TO GET std::size_t, ptrdiff_t ...
# include <iterator> // TO GET iterator_category

# include "TreeNode.hpp"
# include "../type_traits/type_traits.hpp"
# include "map.hpp"
# include "map_rev_iter.hpp"
# include "choose.hpp"

namespace	ft
{
	// CIRCULAR DEPENDENCY
	template< typename Key, typename T, typename Compare, typename Alloc >
	class	map;
}

/*
**	map ITERATOR CLASS DECLARATION
*/

template< typename Key, typename T, bool IsConst,
	typename Compare = std::less<Key>,
	typename Alloc = std::allocator< ft::pair<Key const, T> > >
class map_iter
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
	
	typedef TreeNode< value_type >					node;

	map_iter(void);
	explicit map_iter(node * n, node * prev = 0);

	/*
	**	SFINAE WILL ONLY ALLOW COPYING FROM A NON-CONST src TO
	**	CONST ITERATOR, AND FROM CONST ITERATOR TO CONST ITERATOR.
	*/
	template<bool WasConst>
	map_iter(map_iter<Key, T, WasConst, Compare, Alloc> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);

	~map_iter(void);

	/*
	**	ADDED SPECIALIZATION TO PREVENT iterator ASSIGNMENT
	**	FROM const_iterator.
	*/
	map_iter<Key, T, IsConst, Compare, Alloc> &
		operator=(map_iter<Key, T, false, Compare, Alloc> const & rhs);
	
	bool		operator!=(map_iter const & rhs) const;
	bool		operator==(map_iter const & rhs) const;
	reference	operator*(void) const;
	pointer		operator->(void) const;
	map_iter &	operator++(void);
	map_iter	operator++(int);
	map_iter &	operator--(void);
	map_iter	operator--(int);

private:

	//In order to access private members of non-const from const.
	friend class	map_iter<Key, T, true, Compare, Alloc>;

	/*
	**	ft::map AND map_rev_iter FRIENDSHIPS ARE NEEDED TO ELUDE THE CREATION
	**	OF PUBLIC GETTERS, WHICH ARE NOT PRESENT IN STANDARD ITERATORS.
	**	
	*/

	/*
	**	To interact with and reuse map_iter functionality from map_rev_iter.
	**	Adding explicitly both specializations of IsConst, because IsConst
	**	is either true or false in this instance, and need interaction with
	**	both. IsConst is no longer an undefined variable inside this instance,
	**	that is why it needs to be defined explicitly to include both versions.
	*/
	friend class	map_rev_iter<Key, T, true, Compare, Alloc>;
	friend class	map_rev_iter<Key, T, false, Compare, Alloc>;

	friend class	ft::map<Key, T, Compare, Alloc>;

	key_compare	_comp;
	node *		_node;
	node *		_prev;
};


// MEMBER FUNCTIONS DEFINITIONS


template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>::map_iter(void)
	: _comp(key_compare()), _node(0), _prev(0)
{
	return ;
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>::map_iter(node * n, node * prev)
	: _comp(key_compare()), _node(n), _prev(prev)
{
	return ;
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
template<bool WasConst>
map_iter<Key, T, IsConst,
	Compare, Alloc>::map_iter(map_iter<Key, T, WasConst,
	Compare, Alloc> const & src,
	typename ft::enable_if<IsConst || !WasConst>::type *)
	: _comp(key_compare()), _node(0), _prev(0)
{
	*this = src;
	return ;
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>::~map_iter(void)
{
	return ;
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc> &
	map_iter<Key, T, IsConst, Compare, Alloc>::operator=(map_iter<Key,
		T, false, Compare, Alloc> const & rhs)
{
	/*
	**	NO DEEP COPY NECESSARY BECAUSE THEY ARE ITERATORS THAT ITERATE
	**	OVER THE SAME MAP.
	*/
	this->_comp = rhs._comp;
	this->_node = rhs._node;
	this->_prev = rhs._prev;
	return (*this);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
bool	map_iter<Key, T, IsConst,
			Compare, Alloc>::operator!=(map_iter const & rhs) const
{
	return (this->_node != rhs._node);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
bool	map_iter<Key, T, IsConst,
			Compare, Alloc>::operator==(map_iter const & rhs) const
{
	return (!(*this != rhs));
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
typename map_iter<Key, T, IsConst, Compare, Alloc>::reference
	map_iter<Key, T, IsConst, Compare, Alloc>::operator*(void) const
{
	return (this->_node->getValue());
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
typename map_iter<Key, T, IsConst, Compare, Alloc>::pointer
	map_iter<Key, T, IsConst, Compare, Alloc>::operator->(void) const
{
	return (&(this->_node->getValue()));
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc> &
	map_iter<Key, T, IsConst, Compare, Alloc>::operator++(void)
{
	if (!this->_node)
		return (*this);
	this->_prev = this->_node;
	if (this->_node->getRight())
	{
		this->_node = this->_node->getRight();
		while (this->_node->getLeft())
			this->_node = this->_node->getLeft();
	}
	else
	{
		while (1)
		{
			if (this->_node->getParent())
			{
				if (this->_node == this->_node->getParent()->getLeft())
				{
					this->_node = this->_node->getParent();
					break ;
				}
				this->_node = this->_node->getParent();
			}
			else
			{
				this->_node = 0;
				break ;
			}
		}
	}
	return (*this);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>
	map_iter<Key, T, IsConst, Compare, Alloc>::operator++(int)
{
	map_iter	m(*this);

	++(*this);
	return (m);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc> &
	map_iter<Key, T, IsConst, Compare, Alloc>::operator--(void)
{
	if (!this->_node)
	{
		this->_node = this->_prev;
		return (*this);
	}
	this->_prev = this->_node;
	if (this->_node->getLeft())
	{
		this->_node = this->_node->getLeft();
		while (this->_node->getRight())
			this->_node = this->_node->getRight();
	}
	else
	{
		while (1)
		{
			if (this->_node->getParent())
			{
				if (this->_node == this->_node->getParent()->getRight())
				{
					this->_node = this->_node->getParent();
					break ;
				}
				this->_node = this->_node->getParent();
			}
			else
			{
				this->_node = 0;
				break ;
			}
		}
	}
	return (*this);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>
	map_iter<Key, T, IsConst, Compare, Alloc>::operator--(int)
{
	map_iter	m(*this);

	--(*this);
	return (m);
}

#endif