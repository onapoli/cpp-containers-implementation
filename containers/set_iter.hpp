#ifndef SET_ITER_H
# define SET_ITER_H

# include <cstddef> // TO GET std::size_t, ptrdiff_t ...
# include <iterator> // TO GET iterator_category

# include "TreeNode.hpp"
# include "../type_traits/type_traits.hpp"

/*
**	set ITERATOR CLASS DECLARATION
*/

template< typename T, typename Compare = std::less< T >,
	typename Alloc = std::allocator< T > >
class set_iter
{

public:

	/*
	**	Types for iterator_traits
	*/
	typedef T											key_type;
	typedef	T											value_type;
	typedef	Compare										key_compare;
	typedef	Compare										value_compare;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_pointer		const_pointer;
	typedef typename allocator_type::pointer			pointer;	
	typedef std::size_t									size_type;
	typedef	ptrdiff_t									difference_type;
	typedef std::bidirectional_iterator_tag				iterator_category;
	
	typedef TreeNode< value_type >						node;

	set_iter(void);

	explicit set_iter(node * n, size_type end_offset = 0,
		size_type begin_offset = 0);
	
	set_iter(set_iter const & src);
	~set_iter(void);

	set_iter &		operator=(set_iter const & rhs);
	
	bool			operator!=(set_iter const & rhs) const;
	bool			operator==(set_iter const & rhs) const;
	const_reference	operator*(void) const;
	const_pointer	operator->(void) const;
	set_iter &		operator++(void);
	set_iter		operator++(int);
	set_iter &		operator--(void);
	set_iter		operator--(int);

	node *			getNode(void) const;
	size_type		getEndOffset(void) const;
	size_type		getBeginOffset(void) const;
	void			setEndOffset(size_type offset);
	void			setBeginOffset(size_type offset);

private:

	key_compare	_comp;
	node *		_node;
	size_type	_end_offset;
	size_type	_begin_offset;
};


// MEMBER FUNCTIONS DEFINITIONS


template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>::set_iter(void)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>::set_iter(node * n,
	size_type end_offset, size_type begin_offset)
	: _comp(key_compare()), _node(n), _end_offset(end_offset),
	_begin_offset(begin_offset)
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>::set_iter(set_iter<T, Compare, Alloc> const & src)
	: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
{
	*this = src;
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>::~set_iter(void)
{
	return ;
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc> &
	set_iter<T, Compare, Alloc>::operator=(set_iter const & rhs)
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
bool
	set_iter<T, Compare, Alloc>::operator!=(set_iter const & rhs) const
{
	return (this->_node != rhs._node
		|| this->_begin_offset != rhs._begin_offset
		|| this->_end_offset != rhs._end_offset);
}

template< typename T, typename Compare, typename Alloc >
bool
	set_iter<T, Compare, Alloc>::operator==(set_iter const & rhs) const
{
	return (!(*this != rhs));
}

template< typename T, typename Compare, typename Alloc >
typename set_iter<T, Compare, Alloc>::const_reference
	set_iter<T, Compare, Alloc>::operator*(void) const
{
	return (this->_node->getValue());
}

template< typename T, typename Compare, typename Alloc >
typename set_iter<T, Compare, Alloc>::const_pointer
	set_iter<T, Compare, Alloc>::operator->(void) const
{
	return (&(this->_node->getValue()));
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc> &
	set_iter<T, Compare, Alloc>::operator++(void)
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

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>
	set_iter<T, Compare, Alloc>::operator++(int)
{
	set_iter	s(*this);

	++(*this);
	return (s);
}

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc> &
	set_iter<T, Compare, Alloc>::operator--(void)
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
						this->_node = prev;
						++this->_end_offset;
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

template< typename T, typename Compare, typename Alloc >
set_iter<T, Compare, Alloc>
	set_iter<T, Compare, Alloc>::operator--(int)
{
	set_iter	s(*this);

	--(*this);
	return (s);
}

template< typename T, typename Compare, typename Alloc >
typename set_iter<T, Compare, Alloc>::node *
	set_iter<T, Compare, Alloc>::getNode(void) const
{
	return (this->_node);
}

template< typename T, typename Compare, typename Alloc >
typename set_iter<T, Compare, Alloc>::size_type
	set_iter<T, Compare, Alloc>::getEndOffset(void) const
{
	return (this->_end_offset);
}

template< typename T, typename Compare, typename Alloc >
typename set_iter<T, Compare, Alloc>::size_type
	set_iter<T, Compare, Alloc>::getBeginOffset(void) const
{
	return (this->_begin_offset);
}

template< typename T, typename Compare, typename Alloc >
void
	set_iter<T, Compare, Alloc>::setEndOffset(size_type offset)
{
	this->_end_offset = offset;
	return ;
}

template< typename T, typename Compare, typename Alloc >
void
	set_iter<T, Compare, Alloc>::setBeginOffset(size_type offset)
{
	this->_begin_offset = offset;
	return ;
}

#endif