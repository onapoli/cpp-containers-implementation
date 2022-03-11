#ifndef TREE_NODE_H
# define TREE_NODE_H

# include "../utility/utility.hpp"

/*
**	Class for representing the nodes of the internal
**	Red-Black tree data structure from the map container class.
*/

template< typename T >
class	TreeNode
{
public:

	typedef T	value_type;

	TreeNode(void);
	TreeNode(bool red, TreeNode * parent, value_type * val = 0,
		TreeNode * left = 0, TreeNode * right = 0);
	TreeNode(TreeNode const & src);
	~TreeNode(void);

	TreeNode const &	operator=(TreeNode const & rhs);

	bool			isRed(void) const;
	value_type	&	getValue(void) const;
	TreeNode *		getParent(void) const;
	TreeNode *		getLeft(void) const;
	TreeNode *		getRight(void) const;
	void			setRed(bool red);
	void			setValue(value_type * val);
	void			setParent(TreeNode * parent);
	void			setLeft(TreeNode * left);
	void			setRight(TreeNode * right);

private:

	bool			_red;
	value_type *	_val;
	TreeNode *		_parent;
	TreeNode *		_left;
	TreeNode *		_right;

};

template< typename T >
TreeNode< T >::TreeNode(void) : _red(false), _val(0),
	_parent(0), _left(0), _right(0)
{
	return ;
}

template< typename T >
TreeNode< T >::TreeNode(bool red, TreeNode * parent, value_type * val,
	TreeNode * left, TreeNode * right) : _red(red), _val(val),
	_parent(parent), _left(left), _right(right)
{
	return ;
}

template< typename T >
TreeNode< T >::TreeNode(TreeNode const & src) : _red(false),
	_val(value_type()), _parent(0), _left(0), _right(0)
{
	*this = src;
	return ;
}

template< typename T >
TreeNode< T >::~TreeNode(void)
{
	return ;
}

template< typename T >
TreeNode< T > const &
	TreeNode< T >::operator=(TreeNode const & rhs)
{
	if (this != &rhs)
	{
		this->_red = rhs._red;
		this->_val = rhs._val;
		this->_parent = rhs._parent;
		this->_left = rhs._left;
		this->_right = rhs._right;
	}
	return (*this);
}

template< typename T >
bool	TreeNode< T >::isRed(void) const
{
	return (this->_red);
}

template< typename T >
typename TreeNode< T >::value_type &
	TreeNode< T >::getValue(void) const
{
	return (*this->_val);
}

template< typename T >
TreeNode< T > *	TreeNode< T >::getParent(void) const
{
	return (this->_parent);
}

template< typename T >
TreeNode< T > *	TreeNode< T >::getLeft(void) const
{
	return (this->_left);
}

template< typename T >
TreeNode< T > *	TreeNode< T >::getRight(void) const
{
	return (this->_right);
}

template< typename T >
void	TreeNode< T >::setRed(bool red)
{
	this->_red = red;
	return ;
}

template< typename T >
void	TreeNode< T >::setValue(value_type * val)
{
	this->_val = val;
	return ;
}

template< typename T >
void	TreeNode< T >::setParent(TreeNode * parent)
{
	this->_parent = parent;
	return ;
}

template< typename T >
void	TreeNode< T >::setLeft(TreeNode * left)
{
	this->_left = left;
	return ;
}

template< typename T >
void	TreeNode< T >::setRight(TreeNode * right)
{
	this->_right = right;
	return ;
}

#endif