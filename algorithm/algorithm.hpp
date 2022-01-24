#ifndef ALGORITHM_H
# define ALGORITHM_H

namespace	ft
{
	template< typename InputIterator1, typename	InputIterator2 >
	bool	equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2)
	{
		InputIterator1	it1;
		InputIterator2	it2;

		for (it1 = first1, it2 = first2; it1 != last1; ++it1, ++it2)
		{
			if (*it1 != *it2)
				return (false);
		}
		return (true);
	}

	template< typename InputIterator1, typename	InputIterator2,
		typename BinaryPredicate >
	bool	equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		InputIterator1	it1;
		InputIterator2	it2;

		for (it1 = first1, it2 = first2; it1 != last1; ++it1, ++it2)
		{
			if (!pred(*it1, *it2))
				return (false);
		}
		return (true);
	}

	template< typename InputIterator1, typename	InputIterator2 >
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2)
	{
		InputIterator1	it1;
		InputIterator2	it2;

		for (it1 = first1, it2 = first2; it1 != last1; ++it1, ++it2)
		{
			if (*it1 < *it2)
				return (true);
			if (it2 == last2 || *it2 < *it1)
				return (false);
		}
		return (it2 != last2);
	}

	template< typename InputIterator1, typename	InputIterator2,
		typename Compare >
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		InputIterator1	it1;
		InputIterator2	it2;

		for (it1 = first1, it2 = first2; it1 != last1; ++it1, ++it2)
		{
			if (comp(*it1, *it2))
				return (true);
			if (it2 == last2 || comp(*it2, *it1))
				return (false);
		}
		return (it2 != last2);
	}
}

#endif