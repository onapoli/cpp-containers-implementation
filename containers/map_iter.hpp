#ifndef MAP_ITER_H
# define MAP_ITER_H

# include <iterator>

# include "TreeNode.hpp"

/*
**	STRUCTURE TO SELECT THE RIGHT map_iter reference AND pointer TYPE
**	THROUGH SFINAE
*/

template <bool flag, class IsTrue, class IsFalse>
struct choose;

template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
   typedef IsTrue type;
};

template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
   typedef IsFalse type;
};


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
		typename allocator_type::reference const,
		typename allocator_type::reference>::type	reference;
	typedef typename choose<IsConst,
		typename allocator_type::pointer const,
		typename allocator_type::pointer>::type		pointer;
	
	typedef std::size_t								size_type;
	typedef	ptrdiff_t								difference_type;
	typedef std::bidirectional_iterator_tag			iterator_category;
	
	typedef TreeNode<Key, T>						node;

	map_iter(void);
	explicit map_iter(node * n);

	/*
	**	SFINAE WILL ONLY ALLOW COPYING FROM A NON-CONST src TO
	**	CONST ITERATOR, AND FROM CONST ITERATOR TO CONST ITERATOR.
	*/
	template<bool WasConst>
	map_iter(map_iter<Key, T, WasConst, Compare, Alloc> const & src,
		typename ft::enable_if<IsConst || !WasConst>::type * = 0);

	~map_iter(void);

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

	node *		getNode(void) const;

private:

	//In order to access private members of const from non const.
	friend class	map_iter<Key, T, true, Compare, Alloc>;

	key_compare	_comp;
	node *		_node;
	size_type	_end_offset;
	size_type	_begin_offset;
};


// MEMBER FUNCTIONS DEFINITIONS


template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>::map_iter(void)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	return ;
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
map_iter<Key, T, IsConst, Compare, Alloc>::map_iter(node * n)
	: _comp(key_compare()), _node(n), _end_offset(0), _begin_offset(0)
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
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
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
	this->_end_offset = rhs._end_offset;
	this->_begin_offset = rhs._begin_offset;
	return (*this);
}

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
bool	map_iter<Key, T, IsConst,
			Compare, Alloc>::operator!=(map_iter const & rhs) const
{
	return (this->_node != rhs._node
		|| this->_begin_offset != rhs._begin_offset
		|| this->_end_offset != rhs._end_offset);
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
	node *	prev;

	prev = this->_node;
	if (this->_begin_offset)
		--this->_begin_offset;
	else if (this->_end_offset)
		++this->_end_offset;
	else
	{
		if (this->_node)
		{
			while (1)
			{
				if (this->_node->getLeft()
					&& this->_comp(prev->getValue().first,
						this->_node->getLeft()->getValue().first))
					this->_node = this->_node->getLeft();
				else if (this->_comp(prev->getValue().first,
					this->_node->getValue().first))
					break ;
				else if (this->_node->getRight()
					&& this->_comp(prev->getValue().first,
						this->_node->getRight()->getValue().first))
					this->_node = this->_node->getRight();
				else
				{
					if (this->_node->getParent())
						this->_node = this->_node->getParent();
					else
					{
						this->_node = prev;
						++this->_end_offset;
						break ;
					}
				}
			}				
		}
		else
			++this->_end_offset;
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
	node *	prev;

	prev = this->_node;
	if (this->_end_offset)
		--this->_end_offset;
	else if (this->_begin_offset)
		++this->_begin_offset;
	else
	{
		if (this->_node)
		{
			while (1)
			{
				if (this->_node->getRight()
					&& this->_comp(this->_node->getRight()->getValue().first,
						prev->getValue().first))
					this->_node = this->_node->getRight();
				else if (this->_comp(this->_node->getValue().first,
					prev->getValue().first))
					break ;
				else if (this->_node->getLeft()
					&& this->_comp(this->_node->getLeft()->getValue().first,
						prev->getValue().first))
					this->_node = this->_node->getLeft();
				else
				{
					if (this->_node->getParent())
						this->_node = this->_node->getParent();
					else
					{
						this->_node = prev;
						++this->_begin_offset;
						break ;
					}
				}
			}
		}
		else
			++this->_begin_offset;
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

template< typename Key, typename T, bool IsConst,
	typename Compare, typename Alloc >
typename map_iter<Key, T, IsConst, Compare, Alloc>::node *
	map_iter<Key, T, IsConst, Compare, Alloc>::getNode(void) const
{
	return (this->_node);
}

#endif