/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_traits.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:12:54 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/16 11:43:17 by mdaifi           ###   ########.fr       */
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
}