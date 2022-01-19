#ifndef	ITERATOR_TRAITS_H
# define ITERATOR_TRAITS_H

/*
**	USING struct INSTEAD OF class BECAUSE THERE ARENT ANY PRIVATE FUNCTIONS
**	OR VARIABLES FOR THESE classes, AND struct USES THE PUBLIC SCOPE
**	BY DEFAULT.
*/

namespace	ft
{

	template< typename Iterator >
	struct	iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef	typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	/*
	**	These two specializations are for pointers of fundamental
	**	data types (int*, char*, etc.), which are not user defined,
	**	and as a consequence, they do not have the typenames that
	**	iterator_traits needs (value_type, iterator_category, etc.).
	*/

	template< typename Iterator >
	struct	iterator_traits< Iterator * >
	{
		typedef Iterator						value_type;
		typedef	Iterator*						pointer;
		typedef Iterator&						reference;
		typedef	ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< typename Iterator >
	struct	iterator_traits< const Iterator * >
	{
		typedef Iterator						value_type;
		typedef	const Iterator*					pointer;
		typedef const Iterator&					reference;
		typedef	ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

}

#endif
