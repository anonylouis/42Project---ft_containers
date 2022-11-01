/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcalvie <lcalvie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 15:43:54 by lcalvie           #+#    #+#             */
/*   Updated: 2022/07/08 14:39:22 by lcalvie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2> struct pair
	{
		public :
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			//CONSTRUCTOR
			pair() : first(first_type()), second(second_type()) {};
			
			template<class U, class V>
			pair (const pair<U,V>& copy) : first(copy.first), second(copy.second) {};

			pair (const first_type& a, const second_type& b) : first(a), second(b) {};

			// ASSIGNEMENT OPERATOR
			pair& operator= (const pair& copy) {first=copy.first;second=copy.second;return (*this);};

	};

	// NON MEMBER FUNCTIONS
	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first==rhs.first && lhs.second==rhs.second; };

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs==rhs); };

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); };

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(rhs<lhs); };

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return rhs<lhs; };

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !(lhs<rhs); };

	// MAKE_PAIR
	template <class T1, class T2>
  	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return (ft::pair<T1,T2>(x,y));
	};

}

#endif
