#ifndef PAIR_H
# define PAIR_H

namespace	ft
{
	template< typename T1, typename T2 >
	struct	pair
	{
		typedef	T1	first_type;
		typedef T2	second_type;

		//Member functions

		//constructors
		pair(void);
		template< typename U, typename V >
		pair(pair< U, V > const & pr);
		pair(first_type const & a, second_type const & b);

		pair< T1, T2 > &	operator=(pair< T1, T2> const & pr);

		//attributes
		first_type	first;
		second_type	second;
	};

	template< typename T1, typename T2 >
	pair< T1, T2 >::pair(void) : first(first_type()), second(second_type())
	{
		return ;
	}

	template< typename T1, typename T2 >
	template< typename U, typename V >
	pair< T1, T2 >::pair(pair< U, V > const & pr)
	{
		*this = pr;
		return ;
	}

	template< typename T1, typename T2 >
	pair< T1, T2 >::pair(first_type const & a, second_type const & b)
		: first(a), second(b)
	{
		return ;
	}

	template< typename T1, typename T2 >
	pair< T1, T2 > &	pair< T1, T2 >::operator=(pair< T1, T2 > const & pr)
	{
		if (this != &pr)
		{
			this->first = pr.first;
			this->second = pr.second;
		}
		return (*this);
	}

	//Non member function overloads

	template < typename T1, typename T2 >
  	bool	operator==(pair< T1, T2 > const & lhs, pair< T1, T2> const & rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template < typename T1, typename T2 >
	bool	operator!=(pair< T1, T2 > const & lhs, pair< T1, T2 > const & rhs)
	{
		return (!(lhs == rhs));
	}

	template < typename T1, typename T2 >
	bool	operator<(pair< T1, T2 > const & lhs, pair< T1, T2 > const & rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first)
			&& lhs.second < rhs.second));
	}

	template < typename T1, typename T2 >
	bool	operator<=(pair< T1, T2 > const & lhs, pair< T1, T2 > const & rhs)
	{
		return (!(rhs < lhs));
	}

	template < typename T1, typename T2 >
	bool	operator>(pair< T1, T2 > const & lhs, pair< T1, T2 > const & rhs)
	{
		return (rhs < lhs);
	}

	template < typename T1, typename T2 >
	bool	operator>=(pair< T1, T2 > const & lhs, pair< T1, T2 > const & rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif