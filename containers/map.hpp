#ifndef MAP_H
# define MAP_H

# include <memory>
# include <functional>

# include "../utility/utility.hpp"
# include "TreeNode.hpp"

namespace	ft
{

	template< typename Key, typename T, typename Compare = std::less< Key >,
		typename Alloc = std::allocator< ft::pair<Key const, T> > >
	class	map
	{
	public:

		//Member types
		typedef Key											key_type;
		typedef	T											mapped_type;
		typedef	ft::pair< key_type const, mapped_type >		value_type;
		typedef	Compare										key_compare;
		//typedef /*Nested function class to compare elements*/	value_compare;
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		//typedef	/*map_iterator*/						iterator;
		//...
		typedef	std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;

		//Member functions
		explicit map(key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type());
		/*range constructor*/
		map(map const & src);
		~map(void);

		map &			operator=(map const & rhs);

		//Capacity
		bool			empty(void) const;
		size_type		size(void) const;
		size_type		max_size(void) const;

		//Element access
		mapped_type		operator[](key_type const & k);

		//Modifiers
		bool			insert(value_type const & val);

	private:

		allocator_type		_alloc;
		key_compare			_comp;
		TreeNode<Key, T> *	_root;
		size_type			_size;

		value_type *	_persist_val(value_type const & val);
		bool			_insertNode(TreeNode<Key, T> * node,
							value_type const & val);
		void			_delete_tree(TreeNode<Key, T> * node);
		mapped_type		_search(TreeNode<Key, T> * node,
							key_type const & k);
	
	};

	//Member functions

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::map(key_compare const & comp,
		allocator_type const & alloc) : _alloc(alloc), _comp(comp), _root(0),
		_size(0)
	{
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::map(map const & src)
	{
		*this = src;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::~map(void)
	{
		this->_delete_tree(this->_root);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc> &
		map<Key, T, Compare, Alloc>::operator=(map const & rhs)
	{
		if (this != &rhs)
		{
			this->_alloc = rhs._alloc;
			this->_comp = rhs._comp;
			this->_root = rhs._root; //Needs deep copy
			this->_size = rhs._size;
		}
		return (*this);
	}

	//Capacity

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool	map<Key, T, Compare, Alloc>::empty(void) const
	{
		return (!(this->_size));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::size(void) const
	{
		return (this->_size);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	//Element Access

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::mapped_type
		map<Key, T, Compare, Alloc>::operator[](key_type const & k)
	{
		/*
		**	WHEN ITERATOR IS IMPLEMENTED
		**	return ((*((this->insert(ft::make_pair(k, mapped_type()))).first)).second);
		*/
		return (this->_search(this->_root, k));
	}

	//Modifiers

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool	map<Key, T, Compare, Alloc>::insert(value_type const & val)
	{
		bool		res;

		res = true;
		if (!this->_root)
		{
			this->_root = new TreeNode<Key, T>(false, 0,
				this->_persist_val(val), 0, 0);
		}
		else
			res = this->_insertNode(this->_root, val);
		if (res)
		{
			//Call this->_balanceTree();
			this->_size += 1;
		}
		return (res);
	}

	//Private member functions

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::value_type *
		map<Key, T, Compare, Alloc>::_persist_val(value_type const & val)
	{
		value_type *	res;

		res = this->_alloc.allocate(1);
		this->_alloc.construct(res, val);
		return (res);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	bool	map<Key, T, Compare, Alloc>::_insertNode(TreeNode<Key, T> * node,
				value_type const & val)
	{
		if (this->_comp(val.first, node->getValue().first))
		{
			if (!node->getLeft())
			{
				node->setLeft(new TreeNode<Key, T>(true, node,
					this->_persist_val(val), 0, 0));
				return (true);
			}
			return (this->_insertNode(node->getLeft(), val));
		}
		if (this->_comp(node->getValue().first, val.first))
		{
			if (!node->getRight())
			{
				node->setRight(new TreeNode<Key, T>(true, node,
					this->_persist_val(val), 0, 0));
				return (true);
			}
			return (this->_insertNode(node->getRight(), val));
		}
		return (false);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_delete_tree(TreeNode<Key, T> * node)
	{
		TreeNode<Key, T> *	child;

		if (!node)
			return ;
		child = node->getLeft();
		if (child)
			this->_delete_tree(child);
		child = node->getRight();
		if (child)
			this->_delete_tree(child);
		this->_alloc.destroy(&node->getValue());
		this->_alloc.deallocate(&node->getValue(), 1);
		delete node;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::mapped_type
		map<Key, T, Compare, Alloc>::_search(TreeNode<Key, T> * node,
		key_type const & k)
	{
		//THIS FUNCTION IS PROVISIONAL. IT IS UNNECESSARY.
		value_type *	node_val;

		node_val = &(node->getValue());
		if (node_val->first == k)
			return (node_val->second);
		if (this->_comp(k, node_val->first))
		{
			if (!node->getLeft())
				return (mapped_type());
			return (this->_search(node->getLeft(), k));
		}
		else
		{
			if (!node->getRight())
				return (mapped_type());
			return (this->_search(node->getRight(), k));
		}
	}

}

#endif