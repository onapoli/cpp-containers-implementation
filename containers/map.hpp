#ifndef MAP_H
# define MAP_H

# include <memory>
# include <functional>
# include <cstddef>

#include <iostream> // FOR TESTING

# include "../utility/utility.hpp"
# include "../type_traits/type_traits.hpp"
# include "map_iter.hpp"
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
		/*template <typename Key, typename T, typename Compare, typename Alloc>
		class map<Key,T,Compare,Alloc>::value_compare : std::binary_function<value_type,value_type,bool>
		{// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class map;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}  // constructed with map's comparison object
		public:
			//typedef bool result_type;
			//typedef value_type first_argument_type;
			//typedef value_type second_argument_type;
			
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};*/
		typedef	Alloc										allocator_type;
		typedef	typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef	typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::const_pointer		const_pointer;
		typedef	map_iter<Key, T, Compare, Alloc>			iterator;
		typedef	map_iter<Key, T const, Compare, Alloc>		const_iterator;
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

		//test
		void						printRoot() const;
		void						printTree() const;

	private:

		typedef struct	_s_node_fam
		{
			TreeNode<Key, T> *	parent;
			TreeNode<Key, T> *	sibling;
			TreeNode<Key, T> *	gParent;
			TreeNode<Key, T> *	uncle;
		}				_t_node_fam;
		
		allocator_type		_alloc;
		key_compare			_comp;
		TreeNode<Key, T> *	_root;
		size_type			_size;

		value_type *				_persist_val(value_type const & val);
		//Rebalancing functions
		void						_init_fam(TreeNode<Key, T> * node,
										_t_node_fam & fam);
		void						_left_rotate(TreeNode<Key, T> * node);
		void						_right_rotate(TreeNode<Key, T> * node);
		//rebalancing cases
		void						_left_left(TreeNode<Key, T> * target);
		void						_left_right(TreeNode<Key, T> * target);
		void						_right_right(TreeNode<Key, T> * target);
		void						_right_left(TreeNode<Key, T> * target);
		//insertion and insertion rebalancing functions
		void						_balance_insert(TreeNode<Key, T> * target);
		ft::pair<iterator, bool>	_insert_node(TreeNode<Key, T> * node,
										value_type const & val);
		//erase and erase rebalancing functions
		void						_balance_erase(TreeNode<Key, T> * node);
		TreeNode<Key, T> *			_get_substitute(TreeNode<Key, T> * node);
		void						_delete_node(TreeNode<Key, T> * node);
		//function for deleting the entire tree
		void						_delete_tree(TreeNode<Key, T> * node);
		//utility function
		TreeNode<Key, T> *			_search(key_type const & k) const;
		//test function
		void						_printTree(TreeNode<Key, T> * node,
										int space) const;
	
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
	template <typename InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last,
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

	template< typename Key, typename T, typename Compare, typename Alloc >
	map<Key, T, Compare, Alloc>::map(map const & src)
		: _alloc(allocator_type()), _comp(key_compare()), _root(0), _size(0)
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

	//Iterators

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::begin(void)
	{
		TreeNode<Key, T> *	node;

		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (iterator(node));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::begin(void) const
	{
		TreeNode<Key, T> *	node;

		node = this->_root;
		while (node->getLeft())
			node = node->getLeft();
		return (const_iterator(node));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::end(void)
	{
		TreeNode<Key, T> *	node;
		iterator			it;

		node = this->_root;
		while (node->getRight())
			node = node->getRight();
		it = iterator(node);
		++it;
		return (it);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::end(void) const
	{
		TreeNode<Key, T> *	node;
		iterator			it;

		node = this->_root;
		while (node->getRight())
			node = node->getRight();
		it = const_iterator(node);
		++it;
		return (it);
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
			this->_root = new TreeNode<Key, T>(false, 0,
				this->_persist_val(val), 0, 0);
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
			this->_root = new TreeNode<Key, T>(false, 0,
				this->_persist_val(val), 0, 0);
			this->_size += 1;
			return (iterator(this->_root));
		}
		if (this->_comp(position->first, val.first)
			&& (!position.getNode()->getParent()
				|| this->_comp(position.getNode()->getParent()->getValue().first,
					position->first)))
			pr = this->_insert_node(position.getNode(), val);
		else if(this->_comp(val.first, position->first)
			&& (!position.getNode()->getParent()
				|| this->_comp(position->first,
				position.getNode()->getParent()->getValue().first)))
			pr = this->_insert_node(position.getNode(), val);
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
		iterator		hint;
	
		it = first;
		if (it != last)
		{
			hint = (this->insert(*it)).first;
			++it;
			while (it != last)
			{
				hint = this->insert(hint, *it);
				++it;
			}
		}
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::erase(iterator position)
	{
		if (position == this->end())
			return ;
		this->_delete_node(position.getNode());
		this->_size -= 1;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::erase(key_type const & k)
	{
		TreeNode<Key, T> *	node;

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
				this->erase(last);
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
		size_type			aux_size;
		TreeNode<Key, T> *	aux_root;

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

	//Operations

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::find(key_type const & k)
	{
		TreeNode<Key, T> *	node;

		node = this->_search(k);
		if (node)
			return (iterator(node));
		return (this->end());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::const_iterator
		map<Key, T, Compare, Alloc>::find(key_type const & k) const
	{
		TreeNode<Key, T> *	node;

		node = this->_search(k);
		if (node)
			return (const_iterator(node));
		return (this->end());
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::size_type
		map<Key, T, Compare, Alloc>::count(key_type const & k) const
	{
		TreeNode<Key, T> *	node;

		node = this->_search(k);
		if (node)
			return (1);
		return (0);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	typename map<Key, T, Compare, Alloc>::iterator
		map<Key, T, Compare, Alloc>::lower_bound(key_type const & k)
	{
		TreeNode<Key, T> *	node;
		iterator			it;

		node = this->_root;
		while (k != node->getValue().first)
		{
			if (this->_comp(k, node->getValue().first))
			{
				if (node->getLeft()
					&& (this->_comp(k, node->getLeft()->getValue().first)
					|| k == node->getLeft()->getValue().first))
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
		//NEED CONVERSION FROM iterator TO const_iterator
		const_iterator	it;

		it = this->lower_bound(k);
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
		//NEED CONVERSION FROM iterator TO const_iterator
		const_iterator	it;

		it = this->upper_bound(k);
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

	//test
	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::printRoot(void) const
	{
		std::cout << "root: " << this->_root->getValue().first << std::endl;
		if (this->_root->getParent())
			std::cout << "parent: " << this->_root->getParent()->getValue().first << std::endl;
		std::cout << "root color: " << this->_root->isRed() << std::endl;
		return ;
	}

	//test
	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::printTree(void) const
	{
		this->_printTree(this->_root, 0);
		return ;
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
	void	map<Key, T, Compare, Alloc>::_init_fam(TreeNode<Key, T> * node,
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
	void	map<Key, T, Compare, Alloc>::_left_rotate(TreeNode<Key, T> * node)
	{
		TreeNode<Key, T> *	parent;
		TreeNode<Key, T> *	right_child;

		parent = node->getParent();
		right_child = node->getRight();
		right_child->setParent(parent);
		//update the pointer of node parent
		if (parent)
		{
			parent->getRight() == node ? parent->setRight(right_child)
				: parent->setLeft(right_child);
		} 
		node->setParent(right_child);
		node->setRight(right_child->getLeft());
		right_child->setLeft(node);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_right_rotate(TreeNode<Key, T> * node)
	{
		TreeNode<Key, T> * parent;
		TreeNode<Key, T> * left_child;

		parent = node->getParent();
		left_child = node->getLeft();
		left_child->setParent(parent);
		//update the pointer of node parent
		if (parent)
		{
			parent->getRight() == node ? parent->setRight(left_child)
				: parent->setLeft(left_child);
		}
		node->setParent(left_child);
		node->setLeft(left_child->getRight());
		left_child->setRight(node);
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void
		map<Key, T, Compare, Alloc>::_left_left(TreeNode<Key, T> * target)
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
		map<Key, T, Compare, Alloc>::_left_right(TreeNode<Key, T> * target)
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
		map<Key, T, Compare, Alloc>::_right_right(TreeNode<Key, T> * target)
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
		map<Key, T, Compare, Alloc>::_right_left(TreeNode<Key, T> * target)
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
		map<Key, T, Compare, Alloc>::_balance_insert(TreeNode<Key, T> * target)
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
		map<Key, T, Compare, Alloc>::_insert_node(TreeNode<Key, T> * node,
			value_type const & val)
	{
		if (this->_comp(val.first, node->getValue().first))
		{
			if (!node->getLeft())
			{
				node->setLeft(new TreeNode<Key, T>(true, node,
					this->_persist_val(val), 0, 0));
				this->_balance_insert(node->getLeft());
				return (ft::make_pair<iterator,
					bool>(iterator(node->getLeft()), true));
			}
			return (this->_insert_node(node->getLeft(), val));
		}
		if (this->_comp(node->getValue().first, val.first))
		{
			if (!node->getRight())
			{
				node->setRight(new TreeNode<Key, T>(true, node,
					this->_persist_val(val), 0, 0));
				this->_balance_insert(node->getRight());
				return (ft::make_pair<iterator,
					bool>(iterator(node->getRight()), true));
			}
			return (this->_insert_node(node->getRight(), val));
		}
		return (ft::make_pair<iterator, bool>(iterator(node), false));
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_balance_erase(TreeNode<Key, T> * node)
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
	TreeNode<Key, T> *
		map<Key, T, Compare, Alloc>::_get_substitute(TreeNode<Key, T> * node)
	{
		TreeNode<Key, T> *	substitute;

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
	void	map<Key, T, Compare, Alloc>::_delete_node(TreeNode<Key, T> * node)
	{
		_t_node_fam			node_fam;
		TreeNode<Key, T> *	substitute;
	
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
		if (!node->getParent())
			this->_root = 0;
		delete node;
		this->_size -= 1;
		return ;
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	TreeNode< Key, T > *
		map<Key, T, Compare, Alloc>::_search(key_type const & k) const
	{
		TreeNode<Key, T> *	node;
		value_type *		node_val;

		node = this->_root;
		while (node)
		{
			node_val = &(node->getValue());
			if (node_val->first == k)
				break ;
			if (this->_comp(k, node_val->first))
				node = node->getLeft();
			else
				node = node->getRight();
		}
		return (node);
	}

	template< typename Key, typename T, typename Compare, typename Alloc >
	void	map<Key, T, Compare, Alloc>::_printTree(TreeNode<Key, T> * node,
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
            std::cout << node->getValue().first << std::endl;
            this->_printTree(node->getLeft(), space);
        }
    }

}

#endif