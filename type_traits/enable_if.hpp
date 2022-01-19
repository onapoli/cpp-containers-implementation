#ifndef ENABLE_IF_H
# define ENABLE_IF_H

/*
**	USING struct INSTEAD OF class BECAUSE THERE ARENT ANY PRIVATE FUNCTIONS
**	OR VARIABLES FOR THESE classes, AND struct USES THE PUBLIC SCOPE
**	BY DEFAULT.
*/

namespace	ft
{
	template< bool Cond, typename T = void >
	struct	enable_if
	{};

	template< typename T >
	struct	enable_if<true, T>
	{
		typedef T	type;
	};
}

#endif
