/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:12:54 by mdaifi            #+#    #+#             */
/*   Updated: 2022/03/07 13:35:45 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template <class T, T v>
struct integral_constant {
	typedef T						value_type;
	typedef integral_constant<T,v>	type;
	enum {
		value = v
	};
};

namespace ft
{
	template<bool Cond, class T = void> 
	struct enable_if {};
	
	template<class T> 
	struct enable_if<true, T> {
		typedef T type; 
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;
	
	template<typename T> struct is_integral : public false_type {};
	template<typename T> struct is_integral<const T> : public false_type {};

	template<> struct is_integral<bool> : public true_type {};
	template<> struct is_integral<char> : public true_type {};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<short int> : public true_type {};
	template<> struct is_integral<int> : public true_type {};
	template<> struct is_integral<long int> : public true_type {};
	template<> struct is_integral<long long int> : public true_type {};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short int> : public true_type {};
	template<> struct is_integral<unsigned int> : public true_type {};
	template<> struct is_integral<unsigned long int> : public true_type {};
	template<> struct is_integral<unsigned long long int> : public true_type {};

	template <class InputIterator1, class InputIterator2>
		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
		{
			while (first1 != last1)
			{
				if (!(first1 == first2))
					return false;
				first1++;
				first2++;
			}
			return true;
		};

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
		{
			while (first1 != last1)
			{
				if (!(pred(*first1, *first2)))
					return false;
				first1++;
				first2++;
			}
			return true;
		};

	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1) 
					return false;
				if (*first1 < *first2) 
					return true;
				first1++; 
				first2++;
			}
			return (first2 != last2);
		};

	template <class InputIterator1, class InputIterator2, class Compare>
  		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,InputIterator2 first2, InputIterator2 last2, Compare comp)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1)) 
					return false;
				if (comp(*first1, *first2)) 
					return true;
				first1++; 
				first2++;
			}
			return (first2 != last2);
		};
}