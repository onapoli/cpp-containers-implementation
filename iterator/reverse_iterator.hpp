#ifndef REVERSE_ITERATOR_H
# define REVERSE_ITERATOR_H

# include "iterator_traits.hpp"

namespace	ft
{

	template< typename Iterator >
	class reverse_iterator
	{
	public:

		typedef Iterator	iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category
			iterator_category;
		typedef typename iterator_traits<Iterator>::value_type
			value_type;
		typedef typename iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename iterator_traits<Iterator>::pointer
			pointer;
		typedef typename iterator_traits<Iterator>::reference
			reference;

		reverse_iterator<Iterator>(void);
		/*
		**	THE std VERSION IS:
		**
		**	explicit reverse_iterator<Iterator>(iterator_type it);
		**
		**	BUT SOME TESTS WITH IMPLICIT CONVERSIONS DO NOT PASS
		**	WITH explicit AND CANNOT FIGURE OUT AN ALTERNATIVE WAY.
		*/
		reverse_iterator<Iterator>(iterator_type it);
		//copy constructor function template
		template< typename Iter >
		reverse_iterator<Iterator>(reverse_iterator<Iter> const & rev_it);

		iterator_type		base(void) const;
		reference			operator*(void) const;
		reverse_iterator	operator+(difference_type n) const;
		reverse_iterator&	operator++(void);
		reverse_iterator 	operator++(int);
		reverse_iterator&	operator+=(difference_type n);
		reverse_iterator 	operator-(difference_type n) const;
		reverse_iterator& 	operator--(void);
		reverse_iterator  	operator--(int);
		reverse_iterator&	operator-=(difference_type n);
		pointer 			operator->(void) const;
		reference 			operator[](difference_type n) const;

	private:

		iterator_type	_it;

	};

	template< typename Iterator >
	reverse_iterator<Iterator>::reverse_iterator(void) : _it(0)
	{
		return ;
	}

	template< typename Iterator >
	reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _it(it)
	{
		return ;
	}

	template< typename Iterator >
	template< typename Iter >
	reverse_iterator<Iterator>::reverse_iterator(
		reverse_iterator<Iter> const & rev_it) : _it(rev_it)
	{
		return ;
	}

	template< typename Iterator >
	typename reverse_iterator<Iterator>::iterator_type
		reverse_iterator<Iterator>::base(void) const
	{
		return (this->_it);
	}

	template< typename Iterator >
	typename reverse_iterator<Iterator>::reference
		reverse_iterator<Iterator>::operator*(void) const
	{
		iterator_type	it(this->_it);

		return (*(--it));
	}

	template< typename Iterator >
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator+(difference_type n) const
	{
		return (this->_it - n);
	}

	template< typename Iterator >
	reverse_iterator<Iterator> &
		reverse_iterator<Iterator>::operator++(void)
	{
		this->_it--;
		return (*this);
	}

	template< typename Iterator >
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator	prev(*this);

		++(*this);
		return (prev);
	}

	template< typename Iterator >
	reverse_iterator<Iterator> &
		reverse_iterator<Iterator>::operator+=(difference_type n)
	{
		this->_it -= n;
		return (*this);
	}

	template< typename Iterator >
	reverse_iterator<Iterator>
		reverse_iterator<Iterator>::operator-(difference_type n) const
	{
		return (this->_it + n);
	}

	template< typename Iterator >
	reverse_iterator<Iterator> &	reverse_iterator<Iterator>::operator--(void)
	{
		this->_it++;
		return (*this);
	}

	template< typename Iterator >
	reverse_iterator<Iterator>	reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator	prev(*this);

		--(*this);
		return (prev);
	}

	template< typename Iterator >
	reverse_iterator<Iterator> &
		reverse_iterator<Iterator>::operator-=(difference_type n)
	{
		this->_it += n;
		return (*this);
	}

	template< typename Iterator >
	typename reverse_iterator<Iterator>::pointer
		reverse_iterator<Iterator>::operator->(void) const
	{
		return (&(this->operator*()));
	}

	template< typename Iterator >
	typename reverse_iterator<Iterator>::reference
		reverse_iterator<Iterator>::operator[](difference_type n) const
	{
		return (this->_it[-n-1]);
	}

	// NON-MEMBER functions

	template <class Iterator>
	bool	operator!=(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <class Iterator>
	bool	operator==(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	bool	operator<(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <class Iterator>
	bool	operator<=(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator>
	bool	operator>(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool	operator>=(reverse_iterator<Iterator> const & lhs,
		reverse_iterator<Iterator> const & rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator>
	reverse_iterator<Iterator>
		operator+(typename reverse_iterator<Iterator>::difference_type n,
		reverse_iterator<Iterator> const & rev_it)
	{
		return (rev_it + n);
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type
		operator-(const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

}

#endif

