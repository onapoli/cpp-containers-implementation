#ifndef MAP_ITER_H
# define MAP_ITER_H

# include <iterator>

# include "TreeNode.hpp"

namespace	ft
{

	template< typename Key, typename T, typename Compare = std::less<Key>,
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
		typedef typename allocator_type::reference		reference;
		typedef	typename allocator_type::pointer		pointer;
		typedef std::size_t								size_type;
		typedef	ptrdiff_t								difference_type;
		typedef std::bidirectional_iterator_tag			iterator_category;
		
		typedef TreeNode<Key, T>						node;
	
		map_iter(void);
		explicit map_iter(node * n);
		map_iter(map_iter const & src);
		~map_iter(void);

		map_iter &	operator=(map_iter const & rhs);
		bool		operator!=(map_iter const & rhs) const;
		bool		operator==(map_iter const & rhs) const;
		reference	operator*(void) const;
		pointer		operator->(void) const;
		map_iter &	operator++(void);
		map_iter	operator++(int);
		map_iter &	operator--(void);
		map_iter	operator--(int);
	
	private:
	
		key_compare	_comp;
		node *		_node;
		size_type	_end_offset;
		size_type	_begin_offset;
	};

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>::map_iter(void) : _comp(key_compare()),
		_node(0), _end_offset(0), _begin_offset(0)
	{
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>::map_iter(node * n)
		: _comp(key_compare()), _node(n), _end_offset(0), _begin_offset(0)
	{
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>::map_iter(map_iter const & src)
		: _comp(key_compare()), _node(0), _end_offset(0), _begin_offset(0)
	{
		*this = src;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>::~map_iter(void)
	{
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc> &
		map_iter<Key, T, Compare, Alloc>::operator=(map_iter const & rhs)
	{
		/*
		**	NO DEEP COPY NECESSARY BECAUSE THEY ARE ITERATORS THAT ITERATE
		**	OVER THE SAME MAP.
		*/
		if (this != &rhs)
		{
			this->_comp = rhs._comp;
			this->_node = rhs._node;
			this->_end_offset = rhs._end_offset;
			this->_begin_offset = rhs._begin_offset;
		}
		return (*this);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool
		map_iter<Key, T, Compare, Alloc>::operator!=(map_iter const & rhs) const
	{
		return (this->_node != rhs._node
			|| this->_begin_offset != rhs._begin_offset
			|| this->_end_offset != rhs._end_offset);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool
		map_iter<Key, T, Compare, Alloc>::operator==(map_iter const & rhs) const
	{
		return (!(*this != rhs));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map_iter<Key, T, Compare, Alloc>::reference
		map_iter<Key, T, Compare, Alloc>::operator*(void) const
	{
		return (this->_node->getValue());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map_iter<Key, T, Compare, Alloc>::pointer
		map_iter<Key, T, Compare, Alloc>::operator->(void) const
	{
		return (&(this->_node->getValue()));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc> &
		map_iter<Key, T, Compare, Alloc>::operator++(void)
	{
		node *	aux;
	
		if (this->_begin_offset)
			--this->_begin_offset;
		else if (this->_end_offset)
			++this->_end_offset;
		else
		{
			if (this->_node)
			{
				if (this->_node->getRight())
					this->_node = this->_node->getRight();
				else
				{
					aux = this->_node;
					while (this->_node->getParent())
					{
						this->_node = this->_node->getParent();
						if (this->_comp(aux->getValue().first,
							this->_node->getValue().first))
							break ;
					}
					if (this->_comp(this->_node->getValue().first,
						aux->getValue().first))
					{
						this->_node = aux;
						++this->_end_offset;
					}
				}
			}
			else
				++this->_end_offset;
		}
		return (*this);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>
		map_iter<Key, T, Compare, Alloc>::operator++(int)
	{
		map_iter	m(*this);

		++(*this);
		return (m);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc> &
		map_iter<Key, T, Compare, Alloc>::operator--(void)
	{
		node *	aux;
	
		if (this->_end_offset)
			--this->_end_offset;
		else if (this->_begin_offset)
			++this->_begin_offset;
		else
		{
			if (this->_node)
			{
				if (this->_node->getLeft())
					this->_node = this->_node->getLeft();
				else
				{
					aux = this->_node;
					while (this->_node->getParent())
					{
						this->_node = this->_node->getParent();
						if (this->_comp(this->_node->getValue().first,
							aux->getValue().first))
							break ;
					}
					if (this->_comp(aux->getValue().first,
						this->_node->getValue().first))
					{
						this->_node = aux;
						++this->_begin_offset;
					}
				}
			}
			else
				++this->_begin_offset;
		}
		return (*this);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map_iter<Key, T, Compare, Alloc>
		map_iter<Key, T, Compare, Alloc>::operator--(int)
	{
		map_iter	m(*this);

		--(*this);
		return (m);
	}
	
}

#endif