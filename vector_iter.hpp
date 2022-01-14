#ifndef VECTOR_ITER_H
# define VECTOR_ITER_H

namespace ft
{

	template< typename T >
	class vector_iter
	{

	public:

		/*
		**	Types for iterator_traits
		**
		**	Including these types is the modern way of writing iterators,
		**	instead of inheriting from std::iterator.
		**	Iterator tags are used by <algorithm> functions to determine the
		**	most efficient algorithm to use.
		*/
		typedef T								value_type;
		typedef	T*								pointer;
		typedef T&								reference;
		typedef std::size_t						size_type;
		typedef	ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

		//Default constructor
		vector_iter<T>(void);
		explicit vector_iter<T>(pointer v);
		vector_iter<T>(vector_iter<T> const & src);

		vector_iter<T> &	operator=(vector_iter<T> const & rhs);
		bool				operator!=(vector_iter<T> const & rhs) const;
		bool				operator==(vector_iter<T> const & rhs) const;
		reference			operator*(void) const;
		pointer				operator->(void) const;
		vector_iter<T> &	operator++(void);
		vector_iter<T>		operator++(int);
		vector_iter<T> &	operator--(void);
		vector_iter<T>		operator--(int);
		vector_iter<T>		operator+(difference_type offset) const;
		vector_iter<T>		operator-(difference_type offset) const;
		difference_type		operator-(vector_iter<T> const & rhs) const;
		bool				operator<(vector_iter<T> const & rhs) const;
		bool				operator>(vector_iter<T> const & rhs) const;
		bool				operator<=(vector_iter<T> const & rhs) const;
		bool				operator>=(vector_iter<T> const & rhs) const;
		vector_iter<T> &	operator+=(difference_type offset);
		vector_iter<T> &	operator-=(difference_type offset);
		reference			operator[](difference_type offset) const;

	private:

		pointer	_v;

	};

	template< typename T >
	vector_iter<T>::vector_iter(void) : _v(0)
	{
		std::cout << "vector_iter default constructor called" << std::endl;
		return ;
	}

	template< typename T >
	vector_iter<T>::vector_iter(pointer v) : _v(v)
	{
		std::cout << "vector_iter parameterized constructor called";
		std::cout << std::endl;
		return ;
	}

	template< typename T >
	vector_iter<T>::vector_iter(vector_iter<T> const & src)
	{
		std::cout << "vector_iter copy constructor called" << std::endl;
		*this = src;
		return ;
	}

	template< typename T >
	vector_iter<T> &	vector_iter<T>::operator=(vector_iter<T> const & rhs)
	{
		if (this != &rhs)
			this->_v = rhs._v;
		return (*this);
	}

	template< typename T >
	bool	vector_iter<T>::operator!=(vector_iter<T> const & rhs) const
	{
		return (this->_v != rhs._v);
	}

	template< typename T >
	bool	vector_iter<T>::operator==(vector_iter<T> const & rhs) const
	{
		return (this->_v == rhs._v);
	}

	/*
	**	We do not have access to the inner vector array, instead,
	**	we have access to the vector interface which provides
	**	operator[] and at() to access elements by index.
	*/
	template< typename T >
	typename vector_iter<T>::reference	vector_iter<T>::operator*(void) const
	{
		return (*(this->_v));
	}

	template< typename T >
	typename vector_iter<T>::pointer	vector_iter<T>::operator->(void) const
	{
		return (this->_v);
	}

	template< typename T >
	vector_iter<T> &	vector_iter<T>::operator++(void)
	{
		this->_v += 1;
		return (*this);
	}

	template< typename T >
	vector_iter<T>	vector_iter<T>::operator++(int)
	{
		vector_iter<T>	prev(*this);

		this->_v += 1;
		return (prev);
	}

	template< typename T >
	vector_iter<T> &	vector_iter<T>::operator--(void)
	{
		this->_v -= 1;
		return (*this);
	}

	template< typename T >
	vector_iter<T>	vector_iter<T>::operator--(int)
	{
		vector_iter<T>	prev(*this);

		this->_v -= 1;
		return (prev);
	}

	template< typename T >
	vector_iter<T>	vector_iter<T>::operator+(difference_type offset) const
	{
		vector_iter<T>	res(this->_v + offset);

		return (res);
	}

	template< typename T >
	vector_iter<T>	vector_iter<T>::operator-(difference_type offset) const
	{
		vector_iter<T>	res(this->_v - offset);

		return (res);
	}

	template< typename T >
	typename vector_iter<T>::difference_type	vector_iter<T>::operator-(vector_iter<T> const & rhs) const
	{
		return (this->_v - rhs._v);
	}

	template< typename T >
	bool	vector_iter<T>::operator<(vector_iter<T> const & rhs) const
	{
		return (this->_v < rhs._v);
	}

	template< typename T >
	bool	vector_iter<T>::operator>(vector_iter<T> const & rhs) const
	{
		return (this->_v > rhs._v);
	}

	template< typename T >
	bool	vector_iter<T>::operator<=(vector_iter<T> const & rhs) const
	{
		return (this->_v <= rhs._v);
	}

	template< typename T >
	bool	vector_iter<T>::operator>=(vector_iter<T> const & rhs) const
	{
		return (this->_v >= rhs._v);
	}

	template< typename T >
	vector_iter<T> &	vector_iter<T>::operator+=(difference_type offset)
	{
		this->_v += offset;
		return (*this);
	}

	template< typename T >
	vector_iter<T> &	vector_iter<T>::operator-=(difference_type offset)
	{
		this->_v -= offset;
		return (*this);
	}

	template< typename T >
	typename vector_iter<T>::reference	vector_iter<T>::operator[](difference_type offset) const
	{
		return (*(this->_v + offset));
	}

}

#endif