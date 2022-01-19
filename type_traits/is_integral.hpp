#ifndef IS_INTEGRAL_H
# define IS_INTEGRAL_H

/*
**	USING struct INSTEAD OF class BECAUSE THERE ARENT ANY PRIVATE FUNCTIONS
**	OR VARIABLES FOR THESE classes, AND struct USES THE PUBLIC SCOPE
**	BY DEFAULT.
*/

namespace	ft
{
	/*
	**	THESE TWO HELPER classes ARE PROVIDED TO AVOID DECLARING
	**	THE value VARIABLE IN EACH TEMPLATE SPECIALIZATION, AND
	**	INSTEAD, JUST INHERIT FROM THE APPROPRIATE class DEPENDING
	**	ON THE DESIRED VALUE.
	*/
	struct	is_integral_true
	{
		static const bool	value = true;
	};

	struct	is_integral_false
	{
		static const bool	value = false;
	};

	/*
	**	IF T DOES NOT MATCH ANY OF THE PROVIDED SPECIALIZATION TEMPLATES,
	**	IT IS NOT OF INTEGRAL TYPE. IN THIS WAY WE CAN PERFORM
	**	TYPE CHECKING AT COMPILE TIME.
	*/ 
	template< typename T >
	struct	is_integral : public is_integral_false
	{};

	template<>
	struct	is_integral<bool> : public is_integral_true
	{};

	template<>
	struct	is_integral<char> : public is_integral_true
	{};

	template<>
	struct	is_integral<wchar_t> : public is_integral_true
	{};

	template<>
	struct	is_integral<signed char> : public is_integral_true
	{};

	template<>
	struct	is_integral<short int> : public is_integral_true
	{};

	template<>
	struct	is_integral<int> : public is_integral_true
	{};

	template<>
	struct	is_integral<long int> : public is_integral_true
	{};

	template<>
	struct	is_integral<long long int> : public is_integral_true
	{};

	template<>
	struct	is_integral<unsigned char> : public is_integral_true
	{};

	template<>
	struct	is_integral<unsigned short int> : public is_integral_true
	{};

	template<>
	struct	is_integral<unsigned int> : public is_integral_true
	{};

	template<>
	struct	is_integral<unsigned long int> : public is_integral_true
	{};

	template<>
	struct	is_integral<unsigned long long int> : public is_integral_true
	{};
}

#endif