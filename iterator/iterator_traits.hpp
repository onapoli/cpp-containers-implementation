#ifndef	ITERATOR_TRAITS_H
# define ITERATOR_TRAITS_H

namespace	ft
{

	template< typename Iterator >
	class	iterator_traits
	{
	public:
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
	class	iterator_traits< Iterator * >
	{
	public:
		typedef Iterator						value_type;
		typedef	Iterator*						pointer;
		typedef Iterator&						reference;
		typedef	ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< typename Iterator >
	class	iterator_traits< const Iterator * >
	{
	public:
		typedef Iterator						value_type;
		typedef	const Iterator*					pointer;
		typedef const Iterator&					reference;
		typedef	ptrdiff_t						difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
	};

}

#endif
