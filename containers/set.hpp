#ifndef SET_H
# define SET_H

# include <memory>
# include <functional>
# include <cstddef>

#include <iostream> // FOR TESTING

# include "../utility/utility.hpp"
# include "../type_traits/type_traits.hpp"
# include "../iterator/iterator.hpp"
# include "set_iter.hpp"
# include "set_rev_iter.hpp"
# include "TreeNode.hpp"
# include "../algorithm/algorithm.hpp"

namespace	ft
{

	template< typename T, typename Compare = std::less< T >,
		typename Alloc = std::allocator< T > >
	class	set
	{
	public:

		//Member types
		typedef T											key_type;
		typedef	T											value_type;
		typedef	Compare										key_compare;
		typedef Compare										value_compare;
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	set_iter<T, Compare, Alloc>					iterator;
		typedef	set_iter<T, Compare, Alloc>					const_iterator;
		typedef set_rev_iter<T, Compare, Alloc>				reverse_iterator;
		typedef set_rev_iter<T, Compare, Alloc>				const_reverse_iterator;
		typedef	std::ptrdiff_t								difference_type;
		typedef	std::size_t									size_type;

		typedef TreeNode< value_type >						tree_node;

		//Member functions
		explicit set(key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type());
		//range constructor
		template <typename InputIterator>
		set (InputIterator first, InputIterator last,
       		key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type(),
			typename ft::enable_if< ft::is_integral<InputIterator>::value
			== false >::type * = 0);
		set(set const & src);
		~set(void);

		set &						operator=(set const & rhs);

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

		//Modifiers
		ft::pair<iterator, bool>	insert(value_type const & val);
		iterator					insert(iterator position,
										value_type const & val);
		template <typename InputIterator>
		void						insert(InputIterator first,
										InputIterator last);
		void 						erase(iterator position);
		size_type					erase(value_type const & val);
		void						erase(iterator first, iterator second);
		void						swap(set & x);
		void						clear(void);

		//Observers
		key_compare					key_comp(void) const;
		value_compare				value_comp(void) const;

		//Operations
		iterator					find(value_type const & val) const;
		size_type					count(value_type const & val) const;
		iterator					lower_bound(value_type const & val) const;
		iterator 					upper_bound(value_type const & val) const;
		ft::pair<iterator,iterator>	equal_range(value_type const & val) const;

		//Allocator
		allocator_type				get_allocator() const;

		//test
		void						printTree() const;

	private:

		typedef struct	_s_node_fam
		{
			tree_node *	parent;
			tree_node *	sibling;
			tree_node *	gParent;
			tree_node *	uncle;
		}				_t_node_fam;
		
		allocator_type	_alloc;
		key_compare		_comp;
		tree_node *		_root;
		size_type		_size;

		value_type *				_persist_val(value_type const & val);
		//Rebalancing functions
		void						_init_fam(tree_node * node,
										_t_node_fam & fam);
		void						_left_rotate(tree_node * node);
		void						_right_rotate(tree_node * node);
		//rebalancing cases
		void						_left_left(tree_node * target);
		void						_left_right(tree_node * target);
		void						_right_right(tree_node * target);
		void						_right_left(tree_node * target);
		//insertion and insertion rebalancing functions
		void						_balance_insert(tree_node * target);
		ft::pair<iterator, bool>	_insert_node(tree_node * node,
										value_type const & val);
		//erase and erase rebalancing functions
		void						_balance_erase(tree_node * node);
		tree_node *					_get_substitute(tree_node * node);
		void						_delete_node(tree_node * node);
		//function for deleting the entire tree
		void						_delete_tree(tree_node * node);
		tree_node *					_copy_tree(tree_node * node);
		//utility function
		tree_node *					_search(key_type const & k) const;
		//test function
		void						_printTree(tree_node * node,
										int space) const;
	
	};

	//Member functions

	template< typename T, typename Compare, typename Alloc >
	set<T, Compare, Alloc>::set(key_compare const & comp,
		allocator_type const & alloc) : _alloc(alloc), _comp(comp), _root(0),
		_size(0)
	{
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	template <typename InputIterator>
	set<T, Compare, Alloc>::set(InputIterator first, InputIterator last,
       	key_compare const & comp, allocator_type const & alloc,
		typename ft::enable_if< ft::is_integral<InputIterator>::value
		== false >::type *) : _alloc(alloc), _comp(comp), _root(0), _size(0)
	{
		InputIterator	it;

		for (it = first; it != last; ++it)
		{
			this->insert(*it);
		}
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	set<T, Compare, Alloc>::set(set const & src)
		: _alloc(allocator_type()), _comp(key_compare()), _root(0), _size(0)
	{
		*this = src;
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	set<T, Compare, Alloc>::~set(void)
	{
		this->_delete_tree(this->_root);
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	set<T, Compare, Alloc> &
		set<T, Compare, Alloc>::operator=(set const & rhs)
	{
		if (this != &rhs)
		{
			if (!this->empty())
				this->clear();
			this->_alloc = rhs._alloc;
			this->_comp = rhs._comp;
			//DEEP COPY
			if (rhs._size)
				this->_root = this->_copy_tree(rhs._root);
			this->_size = rhs._size;
		}
		return (*this);
	}

	//Iterators

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::begin(void)
	{
		tree_node *	node;

		if (!this->_size)
			return (iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (iterator(node));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::const_iterator
		set<T, Compare, Alloc>::begin(void) const
	{
		tree_node *	node;

		if (!this->_size)
			return (const_iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (const_iterator(node));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::end(void)
	{
		tree_node *	node;
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

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::const_iterator
		set<T, Compare, Alloc>::end(void) const
	{
		tree_node *		node;
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

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::reverse_iterator
		set<T, Compare, Alloc>::rbegin(void)
	{
		tree_node *	node;
		iterator	it;

		if (!this->_size)
			return (reverse_iterator(this->_root));
		node = this->_root;
		if (node)
		{
			while (node->getRight())
				node = node->getRight();
		}
		it = iterator(node);
		++it;
		return (reverse_iterator(it._node, it._prev));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::const_reverse_iterator
		set<T, Compare, Alloc>::rbegin(void) const
	{
		tree_node *	node;
		iterator	it;

		if (!this->_size)
			return (const_reverse_iterator(this->_root));
		node = this->_root;
		if (node)
		{
			while (node->getRight())
				node = node->getRight();
		}
		it = iterator(node);
		++it;
		return (const_reverse_iterator(it._node, it._prev));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::reverse_iterator
		set<T, Compare, Alloc>::rend(void)
	{
		tree_node *	node;
		iterator	it;

		if (!this->_size)
			return (reverse_iterator(this->_root));
		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		it = iterator(node);
		return (reverse_iterator(it._node, it._prev));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::const_reverse_iterator
		set<T, Compare, Alloc>::rend(void) const
	{
		tree_node *	node;
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

	template< typename T, typename Compare, typename Alloc >
	bool	set<T, Compare, Alloc>::empty(void) const
	{
		return (!(this->_size));
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::size_type
		set<T, Compare, Alloc>::size(void) const
	{
		return (this->_size);
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::size_type
		set<T, Compare, Alloc>::max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	//Modifiers

	template< typename T, typename Compare, typename Alloc >
	ft::pair<typename set<T, Compare, Alloc>::iterator, bool>
		set<T, Compare, Alloc>::insert(value_type const & val)
	{
		ft::pair<iterator, bool>	res;

		if (!this->_root)
		{
			this->_root = new tree_node(false, 0,
				this->_persist_val(val), 0, 0);
			res = ft::make_pair<iterator, bool>(iterator(this->_root), true);
		}
		else
			res = this->_insert_node(this->_root, val);
		if (res.second)
			this->_size += 1;
		return (res);
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::insert(iterator position,
			value_type const & val)
	{
		ft::pair<iterator, bool>	pr;

		if (!this->_root)
		{
			this->_root = new tree_node(false, 0,
				this->_persist_val(val), 0, 0);
			this->_size += 1;
			return (iterator(this->_root));
		}
		if (!position._node)
			pr = this->_insert_node(this->_root, val);
		else if (this->_comp(*position, val)
			&& (!position._node->getParent()
				|| this->_comp(position._node->getParent()->getValue(),
					*position)))
			pr = this->_insert_node(position._node, val);
		else if(this->_comp(val, *position)
			&& (!position._node->getParent()
				|| this->_comp(*position,
				position._node->getParent()->getValue())))
			pr = this->_insert_node(position._node, val);
		else
			pr = this->_insert_node(this->_root, val);
		if (pr.second)
			this->_size += 1;
		return (pr.first);
	}

	template< typename T, typename Compare, typename Alloc >
	template< typename InputIterator>
	void	set<T, Compare, Alloc>::insert(InputIterator first,
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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::erase(iterator position)
	{
		if (position == this->end())
			return ;
		this->_delete_node(position._node);
		this->_size -= 1;
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::size_type
		set<T, Compare, Alloc>::erase(value_type const & val)
	{
		tree_node *	node;

		node = this->_search(val);
		if (!node)
			return (0);
		this->_delete_node(node);
		this->_size -= 1;
		return (1);
	}

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::erase(iterator first, iterator last)
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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::swap(set & x)
	{
		size_type	aux_size;
		tree_node *	aux_root;

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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::clear(void)
	{
		this->_delete_tree(this->_root);
		return ;
	}

	//Observers
	
	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::key_compare
		set<T, Compare, Alloc>::key_comp(void) const
	{
		return (this->_comp);
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::value_compare
		set<T, Compare, Alloc>::value_comp(void) const
	{
		return (this->_comp);
	}

	//Operations

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::find(value_type const & val) const
	{
		tree_node *	node;

		node = this->_search(val);
		if (node)
			return (const_iterator(node));
		return (this->end());
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::size_type
		set<T, Compare, Alloc>::count(key_type const & k) const
	{
		tree_node *	node;

		node = this->_search(k);
		if (node)
			return (1);
		return (0);
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::lower_bound(value_type const & val) const
	{
		tree_node *		node;
		const_iterator	it;

		node = this->_root;
		while (val != node->getValue())
		{
			if (this->_comp(val, node->getValue()))
			{
				if (node->getLeft()
					&& (this->_comp(val, node->getLeft()->getValue())
					|| val == node->getLeft()->getValue()
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
		if (this->_comp(node->getValue(), val)) //SENDS this->end()
			++it;
		return (it);
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::iterator
		set<T, Compare, Alloc>::upper_bound(value_type const & val) const
	{
		const_iterator	it;

		it = this->lower_bound(val);
		if (it != this->end() && *it <= val)
			++it;
		return (it);
	}

	template< typename T, typename Compare, typename Alloc >
	ft::pair<typename set<T, Compare, Alloc>::iterator,
		typename set<T, Compare, Alloc>::iterator>
		set<T, Compare, Alloc>::equal_range(value_type const & val) const
	{
		ft::pair<iterator, iterator>	pr;

		pr.first = this->lower_bound(val);
		pr.second = this->upper_bound(val);
		return (pr);
	}

	//Allocator

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::allocator_type
		set<T, Compare, Alloc>::get_allocator(void) const
	{
		return (this->_alloc);
	}

	//test
	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::printTree(void) const
	{
		this->_printTree(this->_root, 0);
		return ;
	}

	//Private member functions

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::value_type *
		set<T, Compare, Alloc>::_persist_val(value_type const & val)
	{
		value_type *	res;

		res = this->_alloc.allocate(1);
		this->_alloc.construct(res, val);
		return (res);
	}

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_init_fam(tree_node * node,
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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_left_rotate(tree_node * node)
	{
		tree_node *	parent;
		tree_node *	right_child;

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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_right_rotate(tree_node * node)
	{
		tree_node * parent;
		tree_node * left_child;

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

	template< typename T, typename Compare, typename Alloc >
	void
		set<T, Compare, Alloc>::_left_left(tree_node * target)
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

	template< typename T, typename Compare, typename Alloc >
	void
		set<T, Compare, Alloc>::_left_right(tree_node * target)
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

	template< typename T, typename Compare, typename Alloc >
	void
		set<T, Compare, Alloc>::_right_right(tree_node * target)
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

	template< typename T, typename Compare, typename Alloc >
	void
		set<T, Compare, Alloc>::_right_left(tree_node * target)
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

	template< typename T, typename Compare, typename Alloc >
	void
		set<T, Compare, Alloc>::_balance_insert(tree_node * target)
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

	template< typename T, typename Compare, typename Alloc >
	ft::pair<typename set<T, Compare, Alloc>::iterator, bool>
		set<T, Compare, Alloc>::_insert_node(tree_node * node,
			value_type const & val)
	{
		tree_node *	new_node;
	
		if (this->_comp(val, node->getValue()))
		{
			if (!node->getLeft())
			{
				node->setLeft(new tree_node(true, node,
					this->_persist_val(val), 0, 0));
				/*
				**	new_node VARIABLE IS NECESSARY, AS node->getLeft()
				**	MIGHT POINT TO OTHER NODE OR TO NULL AFTER ROTATIONS.
				*/
				new_node = node->getLeft();
				this->_balance_insert(new_node);
				return (ft::make_pair<iterator,
					bool>(iterator(new_node), true));
			}
			return (this->_insert_node(node->getLeft(), val));
		}
		if (this->_comp(node->getValue(), val))
		{
			if (!node->getRight())
			{
				node->setRight(new tree_node(true, node,
					this->_persist_val(val), 0, 0));
				/*
				**	new_node VARIABLE IS NECESSARY, AS node->getRight()
				**	MIGHT POINT TO OTHER NODE OR TO NULL AFTER ROTATIONS.
				*/
				new_node = node->getRight();
				this->_balance_insert(new_node);
				return (ft::make_pair<iterator,
					bool>(iterator(new_node), true));
			}
			return (this->_insert_node(node->getRight(), val));
		}
		return (ft::make_pair<iterator, bool>(iterator(node), false));
	}

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_balance_erase(tree_node * node)
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

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::tree_node *
		set<T, Compare, Alloc>::_get_substitute(tree_node * node)
	{
		tree_node *	substitute;

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

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_delete_node(tree_node * node)
	{
		_t_node_fam	node_fam;
		tree_node *	substitute;
	
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
			this->_alloc.destroy(&node->getValue());
			this->_alloc.deallocate(&node->getValue(), 1);
			delete node;
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
			this->_alloc.destroy(&node->getValue());
			this->_alloc.deallocate(&node->getValue(), 1);
			delete node;
			return ;
		}
		/*
		**	Set value of node to that of substitute and call _delete_node again,
		**	but this time on substitute, so that deallocation and detachment
		**	happens on a leaf node and not on an internal node.
		*/
		this->_alloc.destroy(&node->getValue());
		this->_alloc.deallocate(&node->getValue(), 1);
		node->setValue(this->_persist_val(substitute->getValue()));
		this->_delete_node(substitute);
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_delete_tree(tree_node * node)
	{
		tree_node *	child;

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
		if (!node->getParent())
			this->_root = 0;
		delete node;
		this->_size -= 1;
		return ;
	}

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::tree_node *
		set<T, Compare, Alloc>::_copy_tree(tree_node * node)
	{
		tree_node *	cpy;

		cpy = new tree_node(node->isRed(), 0,
			this->_persist_val(node->getValue()), 0, 0);
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

	template< typename T, typename Compare, typename Alloc >
	typename set<T, Compare, Alloc>::tree_node *
		set<T, Compare, Alloc>::_search(key_type const & k) const
	{
		tree_node *		node;
		value_type *	node_val;

		node = this->_root;
		while (node)
		{
			node_val = &(node->getValue());
			if (*node_val == k)
				break ;
			if (this->_comp(k, *node_val))
				node = node->getLeft();
			else
				node = node->getRight();
		}
		return (node);
	}

	template< typename T, typename Compare, typename Alloc >
	void	set<T, Compare, Alloc>::_printTree(tree_node * node,
				int space) const
    {
        int	i;
	
        if (node)
        {
            space += 10;
            this->_printTree(node->getRight(), space);
            std::cout << "\n";
            for (i = 10; i < space; ++i)
                std::cout << " ";
            std::cout << node->getValue() << std::endl;
            this->_printTree(node->getLeft(), space);
        }
    }

	// Non_Member functions

	template < typename T, typename Compare, typename Alloc >
	bool	operator==(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs )
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template < typename T, typename Compare, typename Alloc >
	bool	operator!=(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs)
	{
		return (!(lhs == rhs));
	}

	template < typename T, typename Compare, typename Alloc >
	bool	operator<(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs)
	{
		typename set<T,Compare,Alloc>::const_iterator	it1;
		typename set<T,Compare,Alloc>::const_iterator	it2;

		for (it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end(); ++it1, ++it2)
		{
			if (it2 == rhs.end() || *it2 < *it1)
				return (false);
			if (*it1 < *it2)
				return (true);
		}
		return (it2 != rhs.end());
	}

	template < typename T, typename Compare, typename Alloc >
	bool	operator<=(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename T, typename Compare, typename Alloc >
	bool	operator>(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs)
	{
		return (rhs < lhs);
	}

	template < typename T, typename Compare, typename Alloc >
	bool	operator>=(set<T,Compare,Alloc> const & lhs,
				set<T,Compare,Alloc> const & rhs)
	{
		return (!(lhs < rhs));
	}

	template < typename T, typename Compare, typename Alloc >
	void	swap(set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
	{
		x.swap(y);
		return ;
	}

}

#endif