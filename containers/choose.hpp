#ifndef CHOOSE_H
# define CHOOSE_H

/*
**	STRUCTURE TO SELECT THE RIGHT ITERATOR reference AND pointer TYPE
**	THROUGH SFINAE AND PARTIAL TEMPLATE SPECIALIZATION.
*/

template <bool flag, class IsTrue, class IsFalse>
struct choose;

template <class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
   typedef IsTrue type;
};

template <class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
   typedef IsFalse type;
};

#endif