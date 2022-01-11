/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:45:20 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/08 15:49:14 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <iostream>

struct input_iterator_tag	{};
struct output_iterator_tag	{};
struct forward_iterator_tag       : public input_iterator_tag			{};
struct bidirectional_iterator_tag : public forward_iterator_tag			{};
struct random_access_iterator_tag : public bidirectional_iterator_tag	{};

template< class Iter >
struct iterator_traits
{
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::reference			reference;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::iterator_category	iterator_category;
};

template< class T >
struct iterator_traits<T*>
{
    typedef std::ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

#endif
