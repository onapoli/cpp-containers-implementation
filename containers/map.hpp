#ifndef MAP_H
# define MAP_H

# include <memory>
# include <functional>
# include <cstddef>

# include "../utility/utility.hpp"
# include "../type_traits/type_traits.hpp"
# include "../iterator/iterator.hpp"
# include "map_iter.hpp"
# include "map_rev_iter.hpp"
# include "TreeNode.hpp"
# include "../algorithm/algorithm.hpp"

namespace	ft
{

	/*
	**	ft::map CLASS DECLARATION
	*/

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

		/*
		**	Nested function class for value_compare type.
		**
		**	in C++98, it is required to inherit
		**	binary_function<value_type,value_type,bool>
		*/
		class value_compare : std::binary_function<value_type,value_type,bool>
		{

		private:

			friend class map;
		
		protected:

			Compare comp;
			// constructed with map's comparison object
			value_compare(Compare c) : comp(c)
			{}
		
		public:
			
			bool operator()(value_type const & x, value_type const & y) const
			{
				return comp(x.first, y.first);
			}
		
		};

		typedef	Alloc										allocator_type;

		typedef TreeNode< value_type >						tree_node;
		/*
		**	THIS GENERATES A NEW allocator from Alloc TO ALLOCATE MEMORY
		**	FOR THE CONTENT OF tree_node, WHICH CONTAINS value_type,
		**	INSTEAD OF ONLY ALLOCATING MEMORY FOR value_type.
		*/
		typedef typename Alloc::template rebind<tree_node>::other
															node_allocator;

		typedef	typename node_allocator::reference			reference;
		typedef typename node_allocator::const_reference	const_reference;
		typedef	typename node_allocator::pointer			pointer;
		typedef	typename node_allocator::const_pointer		const_pointer;
		typedef	map_iter<Key, T, false, Compare, Alloc>		iterator;
		typedef	map_iter<Key, T, true, Compare, Alloc>		const_iterator;
		typedef map_rev_iter<Key, T, false, Compare, Alloc>	reverse_iterator;
		typedef map_rev_iter<Key, T, true, Compare, Alloc>	const_reverse_iterator;
		typedef	std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;

		//Member functions
		explicit map(key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type());
		//range constructor
		template <typename InputIterator>
		map (InputIterator first, InputIterator last,
       		key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type(),
			typename ft::enable_if< ft::is_integral<InputIterator>::value
			== false >::type * = 0);
		map(map const & src);
		~map(void);

		map &						operator=(map const & rhs);

		//Iterators
		iterator					begin(void);
		const_iterator				begin(void)	const;
		iterator					end(void);
		const_iterator				end(void) const;
		reverse_iterator			rbegin(void);
		const_reverse_iterator		rbegin(void) const;
		reverse_iterator			rend(void);
		const_reverse_iterator		rend(void) const;
	
		//Capacity
		bool						empty(void) const;
		size_type					size(void) const;
		size_type					max_size(void) const;

		//Element access
		mapped_type	&				operator[](key_type const & k);

		//Modifiers
		ft::pair<iterator, bool>	insert(value_type const & val);
		iterator					insert(iterator position,
										value_type const & val);
		template <typename InputIterator>
		void						insert(InputIterator first,
										InputIterator last);
		void 						erase(iterator position);
		size_type					erase(key_type const & k);
		void						erase(iterator first, iterator second);
		void						swap(map & x);
		void						clear(void);

		//Observers
		key_compare					key_comp(void) const;
		value_compare				value_comp(void) const;

		//Operations
		iterator					find(key_type const & k);
		const_iterator				find(key_type const & k) const;
		size_type					count(key_type const & k) const;
		iterator					lower_bound(key_type const & k);
		const_iterator				lower_bound(key_type const & k) const;
		iterator					upper_bound(key_type const & k);
		const_iterator 				upper_bound(key_type const & k) const;
		ft::pair<const_iterator,const_iterator>
			equal_range(key_type const & k) const;
		ft::pair<iterator,iterator>	equal_range(key_type const & k);

		//Allocator
		allocator_type				get_allocator() const;

	private:

		typedef struct	_s_node_fam
		{
			pointer	parent;
			pointer	sibling;
			pointer	gParent;
			pointer	uncle;
		}				_t_node_fam;
		
		allocator_type	_alloc;
		node_allocator	_nAlloc;
		key_compare		_comp;
		pointer			_root;
		size_type		_size;

		//Rebalancing functions
		void						_init_fam(pointer node,
										_t_node_fam & fam);
		void						_left_rotate(pointer node);
		void						_right_rotate(pointer node);
		//rebalancing cases
		void						_left_left(pointer target);
		void						_left_right(pointer target);
		void						_right_right(pointer target);
		void						_right_left(pointer target);
		//insertion and insertion rebalancing functions
		void						_balance_insert(pointer target);
		ft::pair<iterator, bool>	_insert_node(pointer node,
										value_type const & val);
		//erase and erase rebalancing functions
		void						_balance_erase(pointer node);
		pointer						_get_substitute(pointer node);
		void						_delete_node(pointer node);
		//function for deleting the entire tree
		void						_delete_tree(pointer node);
		pointer						_copy_tree(pointer node);
		//utility function
		pointer						_search(key_type const & k) const;
	
	};

	//Member functions

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::map(key_compare const & comp,
		allocator_type const & alloc) : _alloc(alloc),
		_nAlloc(node_allocator()), _comp(comp), _root(0), _size(0)
	{
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	template <typename InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last,
       	key_compare const & comp, allocator_type const & alloc,
		typename ft::enable_if< ft::is_integral<InputIterator>::value
		== false >::type *) : _alloc(alloc), _nAlloc(node_allocator()),
		_comp(comp), _root(0), _size(0)
	{
		InputIterator	it;

		for (it = first; it != last; ++it)
		{
			this->insert(*it);
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::map(map const & src)
		: _alloc(allocator_type()), _nAlloc(node_allocator()),
		_comp(key_compare()), _root(0), _size(0)
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
			if (!this->empty())
				this->clear();
			this->_alloc = rhs._alloc;
			this->_nAlloc = rhs._nAlloc;
			this->_comp = rhs._comp;
			//DEEP COPY
			if (rhs._size)
				this->_root = this->_copy_tree(rhs._root);
			this->_size = rhs._size;
		}
		return (*this);
	}

	//Iterators

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::begin(void)
	{
		pointer	node;

		if (!this->_size)
			return (iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (iterator(node));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::begin(void) const
	{
		pointer	node;

		if (!this->_size)
			return (const_iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (const_iterator(node));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::end(void)
	{
		pointer		node;
		iterator	it;

		node = this->_root;
		if (node)
		{
			while (node->getRight())
				node = node->getRight();
		}
		it = iterator(node);
		++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::end(void) const
	{
		pointer			node;
		const_iterator	it;

		node = this->_root;
		if (node)
		{
			while (node->getRight())
				node = node->getRight();
		}
		it = const_iterator(node);
		++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::reverse_iterator
		map<Key, T, Compare, Alloc>::rbegin(void)
	{
		pointer		node;
		iterator	it;

		if (!this->_size)
			return (reverse_iterator(this->_root));
		node = this->_root;
		while (node->getRight())
			node = node->getRight();
		it = iterator(node);
		++it;
		return (reverse_iterator(it._node, it._prev));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
		map<Key, T, Compare, Alloc>::rbegin(void) const
	{
		pointer		node;
		iterator	it;

		if (!this->_size)
			return (const_reverse_iterator(this->_root));
		node = this->_root;
		while (node->getRight())
			node = node->getRight();
		it = iterator(node);
		++it;
		return (const_reverse_iterator(it._node, it._prev));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::reverse_iterator
		map<Key, T, Compare, Alloc>::rend(void)
	{
		pointer		node;
		iterator	it;

		if (!this->_size)
			return (reverse_iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		it = iterator(node);
		return (reverse_iterator(it._node, it._prev));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator
		map<Key, T, Compare, Alloc>::rend(void) const
	{
		pointer		node;
		iterator	it;

		if (!this->_size)
			return (const_reverse_iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		it = iterator(node);
		return (const_reverse_iterator(it._node, it._prev));
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
		return (this->_nAlloc.max_size());
	}

	//Element Access

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::mapped_type &
		map<Key, T, Compare, Alloc>::operator[](key_type const & k)
	{
		return ((*((this->insert(ft::make_pair(k,
			mapped_type()))).first)).second);
	}

	//Modifiers

	template< typename Key, typename T, typename Compare, typename Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
		map<Key, T, Compare, Alloc>::insert(value_type const & val)
	{
		ft::pair<iterator, bool>	res;

		if (!this->_root)
		{
			this->_root = this->_nAlloc.allocate(1);
			this->_nAlloc.construct(this->_root,
				tree_node(false, 0, val, 0, 0));
			res = ft::make_pair<iterator, bool>(iterator(this->_root), true);
		}
		else
			res = this->_insert_node(this->_root, val);
		if (res.second)
			this->_size += 1;
		return (res);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::insert(iterator position,
			value_type const & val)
	{
		ft::pair<iterator, bool>	pr;

		if (!this->_root)
		{
			this->_root = this->_nAlloc.allocate(1);
			this->_nAlloc.construct(this->_root,
				tree_node(false, 0, val, 0, 0));
			this->_size += 1;
			return (iterator(this->_root));
		}
		if (!position._node)
			pr = this->_insert_node(this->_root, val);
		else if (this->_comp(position->first, val.first)
			&& (!position._node->getParent()
				|| this->_comp(position._node->getParent()->getValue().first,
					position->first)))
			pr = this->_insert_node(position._node, val);
		else if(this->_comp(val.first, position->first)
			&& (!position._node->getParent()
				|| this->_comp(position->first,
				position._node->getParent()->getValue().first)))
			pr = this->_insert_node(position._node, val);
		else
			pr = this->_insert_node(this->_root, val);
		if (pr.second)
			this->_size += 1;
		return (pr.first);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	template< typename InputIterator>
	void	map<Key, T, Compare, Alloc>::insert(InputIterator first,
				InputIterator last)
	{
		InputIterator	it;
	
		it = first;
		while (it != last)
		{
			this->insert(*it);
			++it;
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::erase(iterator position)
	{
		if (position == this->end())
			return ;
		this->_delete_node(position._node);
		this->_size -= 1;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::erase(key_type const & k)
	{
		pointer	node;

		node = this->_search(k);
		if (!node)
			return (0);
		this->_delete_node(node);
		this->_size -= 1;
		return (1);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		iterator	aux;

		if (first == this->begin() && last == this->end())
		{
			this->clear();
			return ;
		}
		if (last == this->end())
		{
			--last;
			while (last != first)
			{
				aux = last;
				--last;
				this->erase(aux);
			}
			this->erase(last);
		}
		else
		{
			while (first != last)
			{
				aux = first;		
				++first;
				this->erase(aux);
			}
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::swap(map & x)
	{
		size_type	aux_size;
		pointer		aux_root;

		/*
		**	I DECIDED TO KEEP _alloc AND _comp WHERE THEY WERE ORIGINALLY
		**	ASSIGNED.
		*/
		if (this != &x)
		{
			aux_size = this->_size;
			aux_root = this->_root;
			this->_size = x._size;
			this->_root = x._root;
			x._size = aux_size;
			x._root = aux_root;
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::clear(void)
	{
		this->_delete_tree(this->_root);
		return ;
	}

	//Observers
	
	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::key_compare
		map<Key, T, Compare, Alloc>::key_comp(void) const
	{
		return (this->_comp);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::value_compare
		map<Key, T, Compare, Alloc>::value_comp(void) const
	{
		return (value_compare(this->_comp));
	}

	//Operations

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::find(key_type const & k)
	{
		pointer	node;

		node = this->_search(k);
		if (node)
			return (iterator(node));
		return (this->end());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::find(key_type const & k) const
	{
		pointer	node;

		node = this->_search(k);
		if (node)
			return (const_iterator(node));
		return (this->end());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::count(key_type const & k) const
	{
		pointer	node;

		node = this->_search(k);
		if (node)
			return (1);
		return (0);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::lower_bound(key_type const & k)
	{
		pointer		node;
		iterator	it;

		node = this->_root;
		while (k != node->getValue().first)
		{
			if (this->_comp(k, node->getValue().first))
			{
				if (node->getLeft()
					&& (this->_comp(k, node->getLeft()->getValue().first)
					|| k == node->getLeft()->getValue().first
					|| node->getLeft()->getRight()))
					node = node->getLeft();
				else
					break ;
			}
			else
			{
				if (node->getRight())
					node = node->getRight();
				else
					break ;
			}
		}
		it = iterator(node);
		if (this->_comp(node->getValue().first, k)) //SENDS this->end()
			++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::lower_bound(key_type const & k) const
	{
		pointer			node;
		const_iterator	it;

		node = this->_root;
		while (k != node->getValue().first)
		{
			if (this->_comp(k, node->getValue().first))
			{
				if (node->getLeft()
					&& (this->_comp(k, node->getLeft()->getValue().first)
					|| k == node->getLeft()->getValue().first
					|| node->getLeft()->getRight()))
					node = node->getLeft();
				else
					break ;
			}
			else
			{
				if (node->getRight())
					node = node->getRight();
				else
					break ;
			}
		}
		it = const_iterator(node);
		if (this->_comp(node->getValue().first, k)) //SENDS this->end()
			++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::upper_bound(key_type const & k)
	{
		iterator	it;

		it = this->lower_bound(k);
		if (it != this->end() && it->first <= k)
			++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::upper_bound(key_type const & k) const
	{
		const_iterator	it;

		it = this->lower_bound(k);
		if (it != this->end() && it->first <= k)
			++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator,
		typename map<Key, T, Compare, Alloc>::iterator>
		map<Key, T, Compare, Alloc>::equal_range(key_type const & k)
	{
		ft::pair<iterator, iterator>	pr;

		pr.first = this->lower_bound(k);
		pr.second = this->upper_bound(k);
		return (pr);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc>::const_iterator,
		typename map<Key, T, Compare, Alloc>::const_iterator>
		map<Key, T, Compare, Alloc>::equal_range(key_type const & k) const
	{
		ft::pair<const_iterator, const_iterator>	pr;

		pr.first = this->lower_bound(k);
		pr.second = this->upper_bound(k);
		return (pr);
	}

	//Allocator

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::allocator_type
		map<Key, T, Compare, Alloc>::get_allocator(void) const
	{
		return (this->_alloc);
	}

	//Private member functions

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_init_fam(pointer node,
				_t_node_fam & fam)
	{
		fam.parent = node->getParent();
		fam.sibling = 0;
		fam.gParent = 0;
		fam.uncle = 0;
		if (!fam.parent)
			return ;
		fam.sibling = (fam.parent)->getLeft() != node ?
			(fam.parent)->getLeft() : (fam.parent)->getRight();
		fam.gParent = (fam.parent)->getParent();
		if (!fam.gParent)
			return ;
		fam.uncle = (fam.gParent)->getLeft() != fam.parent ?
			(fam.gParent)->getLeft() : (fam.gParent)->getRight();
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_left_rotate(pointer node)
	{
		pointer	parent;
		pointer	right_child;

		parent = node->getParent();
		right_child = node->getRight();
		right_child->setParent(parent);
		//update the pointer of node parent
		if (parent)
		{
			parent->getRight() == node ? parent->setRight(right_child)
				: parent->setLeft(right_child);
		}
		else
			this->_root = right_child;
		node->setParent(right_child);
		if (right_child->getLeft())
			right_child->getLeft()->setParent(node);
		node->setRight(right_child->getLeft());
		right_child->setLeft(node);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_right_rotate(pointer node)
	{
		pointer parent;
		pointer left_child;

		parent = node->getParent();
		left_child = node->getLeft();
		left_child->setParent(parent);
		//update the pointer of node parent
		if (parent)
		{
			parent->getRight() == node ? parent->setRight(left_child)
				: parent->setLeft(left_child);
		}
		else
			this->_root = left_child;
		node->setParent(left_child);
		if (left_child->getRight())
			left_child->getRight()->setParent(node);
		node->setLeft(left_child->getRight());
		left_child->setRight(node);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_left_left(pointer target)
	{
		/*
		**	IF THIS FUNCTION GETS CALLED, IT MEANS target HAS A GRANDPARENT,
		**	BECAUSE THE COLOR OF UNCLE WAS CHECKED.
		**
		**	1. Right rotate grandParent of target.
		**	2. Set color of parent of target to black.
		**	3. Set color of what was previously grandParent of target,
		**		which now is rightChild of parent of target, to red.
		**	4. If parent of target does not have a parent, this means
		**		that the node that at the beginning was the grandParent
		**		of target was the root of the tree. So we change the
		**		root pointer to the current parent of target.
		*/
		this->_right_rotate(target->getParent()->getParent());
		if (target->getParent()->isRed())
			target->getParent()->setRed(false);
		else
			target->getParent()->setRed(true);
		/*
		**	IT IS SAFE TO ASSUME THAT target->getParent()->getRight()
		**	EXISTS AFTER ROTATION
		*/
		if (target->getParent()->getRight()->isRed())
			target->getParent()->getRight()->setRed(false);
		else
			target->getParent()->getRight()->setRed(true);
		if (!target->getParent()->getParent())
			this->_root = target->getParent();
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_left_right(pointer target)
	{
		/*
		**	IF THIS FUNCTION GETS CALLED, IT MEANS target HAS A GRANDPARENT,
		**	BECAUSE THE COLOR OF UNCLE WAS CHECKED.
		**
		**	1. Left rotate Parent of target.
		**	2. Right rotate the new Parent of target, which is the previous
		**		grandParent of target.
		**	3. Set color of target to black.
		**	4. Set color of what at the beginning was grandParent of target,
		**		which now is rightChild of target, to red.
		**	5. If target does not have a parent, this means that the previous
		**		grandParent of target was thee root node. So we change the
		**		root pointer to target.
		*/
		this->_left_rotate(target->getParent());
		this->_right_rotate(target->getParent());
		if (target->isRed())
			target->setRed(false);
		else
			target->setRed(true);
		/*
		**	IT IS SAFE TO ASSUME THAT target->getRight()
		**	EXISTS AFTER ROTATIONS
		*/
		if (target->getRight()->isRed())
			target->getRight()->setRed(false);
		else
			target->getRight()->setRed(true);
		if (!target->getParent())
			this->_root = target;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_right_right(pointer target)
	{
		/*
		**	IF THIS FUNCTION GETS CALLED, IT MEANS target HAS A GRANDPARENT,
		**	BECAUSE THE COLOR OF UNCLE WAS CHECKED.
		**
		**	1. Left rotate grandParent of target.
		**	2. Set color of parent of target to black.
		**	3. Set color of what was previously grandParent of target,
		**		which now is leftChild of parent of target, to red.
		**	4. If parent of target does not have a parent, this means
		**		that the node that at the beginning was the grandParent
		**		of target was the root of the tree. So we change the
		**		root pointer to the current parent of target.
		*/
		this->_left_rotate(target->getParent()->getParent());
		if (target->getParent()->isRed())
			target->getParent()->setRed(false);
		else
			target->getParent()->setRed(true);
		/*
		**	IT IS SAFE TO ASSUME THAT target->getParent()->getLeft()
		**	EXISTS AFTER ROTATION
		*/
		if (target->getParent()->getLeft()->isRed())
			target->getParent()->getLeft()->setRed(false);
		else
			target->getParent()->getLeft()->setRed(true);
		if (!target->getParent()->getParent())
			this->_root = target->getParent();
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_right_left(pointer target)
	{
		/*
		**	IF THIS FUNCTION GETS CALLED, IT MEANS target HAS A GRANDPARENT,
		**	BECAUSE THE COLOR OF UNCLE WAS CHECKED.
		**
		**	1. Right rotate Parent of target.
		**	2. Left rotate the new Parent of target, which is the previous
		**		grandParent of target.
		**	3. Set color of target to black.
		**	4. Set color of what at the beginning was grandParent of target,
		**		which now is leftChild of target, to red.
		**	5. If target does not have a parent, this means that the previous
		**		grandParent of target was thee root node. So we change the
		**		root pointer to target.
		*/
		this->_right_rotate(target->getParent());
		this->_left_rotate(target->getParent());
		if (target->isRed())
			target->setRed(false);
		else
			target->setRed(true);
		/*
		**	IT IS SAFE TO ASSUME THAT target->getLeft()
		**	EXISTS AFTER ROTATIONS
		*/
		if (target->getLeft()->isRed())
			target->getLeft()->setRed(false);
		else
			target->getLeft()->setRed(true);
		if (!target->getParent())
			this->_root = target;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_balance_insert(pointer target)
	{
		_t_node_fam	fam;

		this->_init_fam(target, fam);
		while (fam.parent && (fam.parent)->isRed())
		{
			if (fam.uncle && (fam.uncle)->isRed())
			{
				(fam.parent)->setRed(false);
				(fam.uncle)->setRed(false);
				if ((fam.gParent)->getParent())
					(fam.gParent)->setRed(true);
				target = fam.gParent;
				this->_init_fam(target, fam);
			}
			else
			{
				/*
				**	SEEMS SAFE TO ASSUME fam.gParent IS NOT NULL
				**	WHEN ENTERING THIS BLOCK.
				*/
				if (fam.parent == (fam.gParent)->getLeft() &&
						target == (fam.parent)->getLeft())
					this->_left_left(target);
				else if (fam.parent == (fam.gParent)->getLeft() &&
							target == (fam.parent)->getRight())
					this->_left_right(target);
				else if (fam.parent == (fam.gParent)->getRight() &&
							target == (fam.parent)->getRight())
					this->_right_right(target);
				else
					this->_right_left(target);
				break ;
			}
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	ft::pair<typename map<Key, T, Compare, Alloc>::iterator, bool>
		map<Key, T, Compare, Alloc>::_insert_node(pointer node,
			value_type const & val)
	{
		pointer	new_node;
	
		if (this->_comp(val.first, node->getValue().first))
		{
			if (!node->getLeft())
			{
				/*
				**	new_node VARIABLE IS NECESSARY, AS node->getLeft()
				**	MIGHT POINT TO OTHER NODE OR TO NULL AFTER ROTATIONS.
				*/
				new_node = this->_nAlloc.allocate(1);
				this->_nAlloc.construct(new_node,
					tree_node(true, node, val, 0, 0));
				node->setLeft(new_node);
				this->_balance_insert(new_node);
				return (ft::make_pair<iterator,
					bool>(iterator(new_node), true));
			}
			return (this->_insert_node(node->getLeft(), val));
		}
		if (this->_comp(node->getValue().first, val.first))
		{
			if (!node->getRight())
			{
				/*
				**	new_node VARIABLE IS NECESSARY, AS node->getRight()
				**	MIGHT POINT TO OTHER NODE OR TO NULL AFTER ROTATIONS.
				*/
				new_node = this->_nAlloc.allocate(1);
				this->_nAlloc.construct(new_node,
					tree_node(true, node, val, 0, 0));
				node->setRight(new_node);
				this->_balance_insert(new_node);
				return (ft::make_pair<iterator,
					bool>(iterator(new_node), true));
			}
			return (this->_insert_node(node->getRight(), val));
		}
		return (ft::make_pair<iterator, bool>(iterator(node), false));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_balance_erase(pointer node)
	{
		_t_node_fam	fam;

		this->_init_fam(node, fam);
		if (node->isRed() || this->_root == node)
		{
			node->setRed(false);
			return ;
		}
		if (!fam.sibling)
			this->_balance_erase(fam.parent);
		else
		{
			if ((fam.sibling)->isRed())
			{
				(fam.parent)->setRed(true);
				(fam.sibling)->setRed(false);
				if (fam.sibling == (fam.parent)->getLeft())
					this->_right_rotate(fam.parent);
				else
					this->_left_rotate(fam.parent);
				this->_balance_erase(node);
			}
			else
			{
				if (((fam.sibling)->getLeft() && (fam.sibling)->getLeft()->isRed())
					|| ((fam.sibling)->getRight() && (fam.sibling)->getRight()->isRed()))
				{
					if ((fam.parent)->getLeft() == fam.sibling)
					{
						if ((fam.sibling)->getLeft()
							&& (fam.sibling)->getLeft()->isRed())
						{
							(fam.sibling)->getLeft()->setRed(false);
							this->_left_left((fam.sibling)->getLeft());
						}
						else
						{
							(fam.sibling)->getRight()->setRed(false);
							this->_left_right((fam.sibling)->getRight());
						}
					}
					else
					{
						if ((fam.sibling)->getRight()
							&& (fam.sibling)->getRight()->isRed())
						{
							(fam.sibling)->getRight()->setRed(false);
							this->_right_right((fam.sibling)->getRight());
						}
						else
						{
							(fam.sibling)->getLeft()->setRed(false);
							this->_right_left((fam.sibling)->getLeft());
						}
					}
				}
				else
				{
					(fam.sibling)->setRed(true);
					if ((fam.parent)->isRed())
						(fam.parent)->setRed(false);
					else
						this->_balance_erase(fam.parent);
				}
			}
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::pointer
		map<Key, T, Compare, Alloc>::_get_substitute(pointer node)
	{
		pointer	substitute;

		substitute = 0;
		/*
		**	Substitute of node to be erased will be the leftmost
		**	node of right node when node to be erased has two non NULL
		**	childs.
		*/
		if (node->getLeft() && node->getRight())
		{
			substitute = node->getRight();
			while (substitute->getLeft())
				substitute = substitute->getLeft();
		}
		else if (node->getLeft())
			substitute = node->getLeft();
		else if (node->getRight())
			substitute = node->getRight();
		return (substitute);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_delete_node(pointer node)
	{
		_t_node_fam	node_fam;
		pointer		substitute;
	
		this->_init_fam(node, node_fam);
		substitute = this->_get_substitute(node);
		if (!substitute)
		{
			if (node_fam.parent)
			{
				/*
				**	First rebalance using node to get t_node_fam, if passing 0
				**	that data would not be available.
				*/
				this->_balance_erase(node);
				//	Then assign null to parent pointer to node.
				(node_fam.parent)->getLeft() == node
					? (node_fam.parent)->setLeft(0)
					: (node_fam.parent)->setRight(0);
			}
			else
				this->_root = 0;
			this->_nAlloc.destroy(node);
			this->_nAlloc.deallocate(node, 1);
			return ;
		}
		else if (!node->getLeft() || !node->getRight())
		{
			if (node_fam.parent)
			{
				(node_fam.parent)->getLeft() == node
					? (node_fam.parent)->setLeft(substitute)
					: (node_fam.parent)->setRight(substitute);
				substitute->setParent(node_fam.parent);
			}
			else
			{
				/*
				**	node is root, so substitute didn't have sibling,
				**	uncle and gParent already.
				*/
				substitute->setParent(0);
				this->_root = substitute;
			}
			if (!node->isRed())
				this->_balance_erase(substitute);
			else
				substitute->setRed(false);
			this->_nAlloc.destroy(node);
			this->_nAlloc.deallocate(node, 1);
			return ;
		}
		/*
		**	Set value of node to that of substitute and call _delete_node again,
		**	but this time on substitute, so that deallocation and detachment
		**	happens on a leaf node and not on an internal node.
		*/
		this->_alloc.destroy(&node->getValue());
		this->_alloc.construct(&node->getValue(), substitute->getValue());
		this->_delete_node(substitute);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_delete_tree(pointer node)
	{
		pointer	child;

		if (!node)
			return ;
		child = node->getLeft();
		if (child)
			this->_delete_tree(child);
		child = node->getRight();
		if (child)
			this->_delete_tree(child);
		if (!node->getParent())
			this->_root = 0;
		this->_nAlloc.destroy(node);
		this->_nAlloc.deallocate(node, 1);
		this->_size -= 1;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::pointer
		map<Key, T, Compare, Alloc>::_copy_tree(pointer node)
	{
		pointer	cpy;

		cpy = this->_nAlloc.allocate(1);
		this->_nAlloc.construct(cpy,
			tree_node(node->isRed(), 0, node->getValue(), 0, 0));
		if (node->getLeft())
		{
			cpy->setLeft(this->_copy_tree(node->getLeft()));
			cpy->getLeft()->setParent(cpy);
		}
		if (node->getRight())
		{
			cpy->setRight(this->_copy_tree(node->getRight()));
			cpy->getRight()->setParent(cpy);
		}
		return (cpy);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::pointer
		map<Key, T, Compare, Alloc>::_search(key_type const & k) const
	{
		pointer		node;

		node = this->_root;
		while (node)
		{
			if (node->getValue().first == k)
				break ;
			if (this->_comp(k, node->getValue().first))
				node = node->getLeft();
			else
				node = node->getRight();
		}
		return (node);
	}

	// Non_Member functions

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator==(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator!=(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs)
	{
		return (!(lhs == rhs));
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator<(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs)
	{
		typename map<Key,T,Compare,Alloc>::const_iterator	it1;
		typename map<Key,T,Compare,Alloc>::const_iterator	it2;

		for (it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end(); ++it1, ++it2)
		{
			if (it2 == rhs.end()
				|| it2->first < it1->first
				|| (it2->first == it1->first && it2->second < it1->second))
				return (false);
			if (it1->first < it2->first
				|| (it1->first == it2->first && it1->second < it2->second))
				return (true);
		}
		return (it2 != rhs.end());
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator<=(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator>(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs)
	{
		return (rhs < lhs);
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	bool	operator>=(map<Key,T,Compare,Alloc> const & lhs,
				map<Key,T,Compare,Alloc> const & rhs)
	{
		return (!(lhs < rhs));
	}

	template < typename Key, typename T, typename Compare, typename Alloc >
	void	swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
		return ;
	}

}

#endif