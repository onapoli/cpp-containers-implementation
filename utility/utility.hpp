#ifndef UTILITY_H
# define UTILITY_H

# include "pair.hpp"

namespace	ft
{
	template < typename T1, typename T2 >
	pair< T1, T2 >	make_pair(T1 x, T2 y)
	{
		return (pair< T1, T2 >(x, y));
	}
}

#endif