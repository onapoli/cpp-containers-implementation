#ifndef VECTOR_ITER_H
# define VECTOR_ITER_H

# include "vector.hpp"

namespace ft
{

	template < typename T, typename Alloc > class vector;

	template< typename T, typename Alloc = std::allocator< T > >
	class vector_iter
	{

	public:

		typedef T								value_type;
		typedef	T*								pointer;
		typedef T&								reference;
		typedef	T const*						const_pointer;
		typedef T const&						const_reference;
		typedef std::size_t						size_type;
		typedef	ptrdiff_t						difference_type;
		/*
		**	Including this type is the modern way of writing iterators,
		**	instead of inheriting from std::iterator.
		**	Iterator tags are used by <algorithm> functions to determine the
		**	most efficient algorithm to use.
		*/
		typedef std::random_access_iterator_tag	iterator_category;

		//Default constructor
		vector_iter<T, Alloc>(void);
		vector_iter<T, Alloc>(ft::vector<T, Alloc> & v, size_type index);
		vector_iter<T, Alloc>(vector_iter<T, Alloc> const & src);
		~vector_iter<T, Alloc>(void);

		vector_iter<T, Alloc> &	operator=(vector_iter<T,
									Alloc> const & rhs);
		bool					operator!=(vector_iter<T,
									Alloc> const & rhs) const;
		bool					operator==(vector_iter<T,
									Alloc> const & rhs) const;
		reference				operator*(void) const;
		pointer					operator->(void) const;
		vector_iter<T, Alloc> &	operator++(void);
		vector_iter<T, Alloc>	operator++(int);
		vector_iter<T, Alloc> &	operator--(void);
		vector_iter<T, Alloc>	operator--(int);
		vector_iter<T, Alloc>	operator+(difference_type offset) const;
		vector_iter<T, Alloc>	operator-(difference_type offset) const;
		difference_type			operator-(vector_iter<T,
									Alloc> const & rhs) const;
		bool					operator<(vector_iter<T,
									Alloc> const & rhs) const;
		bool					operator>(vector_iter<T,
									Alloc> const & rhs) const;
		bool					operator<=(vector_iter<T,
									Alloc> const & rhs) const;
		bool					operator>=(vector_iter<T,
									Alloc> const & rhs) const;
		vector_iter<T, Alloc> &	operator+=(difference_type offset);
		vector_iter<T, Alloc> &	operator-=(difference_type offset);
		reference				operator[](difference_type offset) const;

	private:

		ft::vector<T, Alloc> *	_v;
		size_type				_index;

	};

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>::vector_iter(void) : _v(0), _index(0)
	{
		std::cout << "vector_iter default constructor called" << std::endl;
		return ;
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>::vector_iter(ft::vector<T, Alloc> & v,
		size_type index) : _v(&v), _index(index)
	{
		std::cout << "vector_iter parameterized constructor called";
		std::cout << std::endl;
		return ;
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>::vector_iter(vector_iter<T, Alloc> const & src)
	{
		std::cout << "vector_iter copy constructor called" << std::endl;
		*this = src;
		return ;
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>::~vector_iter(void)
	{
		std::cout << "vector_iter destructor called" << std::endl;
		return ;
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc> &	vector_iter<T, Alloc>::operator=(vector_iter<T,
		Alloc> const & rhs)
	{
		if (this != &rhs)
		{
			this->_v = rhs._v;
			this->_index = rhs._index;
		}
		return (*this);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator!=(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_v != rhs._v || this->_index != rhs._index);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator==(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_v == rhs._v && this->_index == rhs._index);
	}

	/*
	**	We do not have access to the inner vector array, instead,
	**	we have access to the vector interface which provides
	**	operator[] and at() to access elements by index.
	*/
	template< typename T, typename Alloc >
	typename vector_iter<T, Alloc>::reference	vector_iter<T,
		Alloc>::operator*(void) const
	{
		return ((*(this->_v))[this->_index]);
	}

	template< typename T, typename Alloc >
	typename vector_iter<T, Alloc>::pointer	vector_iter<T,
		Alloc>::operator->(void) const
	{
		return (&(this->operator*()));
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc> &	vector_iter<T, Alloc>::operator++(void)
	{
		this->_index += 1;
		return (*this);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>	vector_iter<T, Alloc>::operator++(int)
	{
		vector_iter<T, Alloc>	prev(*this);

		this->_index += 1;
		return (prev);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc> &	vector_iter<T, Alloc>::operator--(void)
	{
		this->_index -= 1;
		return (*this);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>	vector_iter<T, Alloc>::operator--(int)
	{
		vector_iter<T, Alloc>	prev(*this);

		this->_index -= 1;
		return (prev);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>	vector_iter<T,
		Alloc>::operator+(difference_type offset) const
	{
		vector_iter<T, Alloc>	res(*this->_v, this->_index + offset);

		return (res);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc>	vector_iter<T,
		Alloc>::operator-(difference_type offset) const
	{
		vector_iter<T, Alloc>	res(*this->_v, this->_index - offset);

		return (res);
	}

	template< typename T, typename Alloc >
	typename vector_iter<T, Alloc>::difference_type	vector_iter<T,
		Alloc>::operator-(vector_iter<T, Alloc> const & rhs) const
	{
		return (this->_index - rhs._index);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator<(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_index < rhs._index);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator>(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_index > rhs._index);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator<=(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_index <= rhs._index);
	}

	template< typename T, typename Alloc >
	bool	vector_iter<T, Alloc>::operator>=(vector_iter<T,
		Alloc> const & rhs) const
	{
		return (this->_index >= rhs._index);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc> &	vector_iter<T,
		Alloc>::operator+=(difference_type offset)
	{
		this->_index += offset;
		return (*this);
	}

	template< typename T, typename Alloc >
	vector_iter<T, Alloc> &	vector_iter<T,
		Alloc>::operator-=(difference_type offset)
	{
		this->_index -= offset;
		return (*this);
	}

	template< typename T, typename Alloc >
	typename vector_iter<T, Alloc>::reference	vector_iter<T,
		Alloc>::operator[](difference_type offset) const
	{
		return ((*(this->_v))[offset]);
	}

}

#endif