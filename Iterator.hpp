/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 13:42:20 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/10 12:23:21 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include "Iterator_traits.hpp"
# include <iostream>

namespace ft
{
	template< class Iterator >
	class Vector_iterator : public iterator <
		typename iterator_traits<Iterator>::iterator_category,
		typename iterator_traits<Iterator>::value_type,
		typename iterator_traits<Iterator>::difference_type,
		typename iterator_traits<Iterator>::pointer,
		typename iterator_traits<Iterator>::reference>
	{
		private:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

			pointer	_it;

		public:
			Vector_iterator() : _it(nullptr) {};
			explicit Vector_iterator( iterator_type it) {
				_it = it;
			};

			template<class iter>
				Vector_iterator(const Vector_iterator<iter> &it) {
				_it = it._it;
			};

			~Vector_iterator() {};

			reference		&operator*() const {
				return (*_it);
			};

			Vector_iterator	&operator+( difference_type n ) const {
				Vector_iterator	tmp(*this);

				return (tmp += n);
			};

			Vector_iterator	&operator++() {
				_it++;
				return (*this);
			};

			Vector_iterator	operator++( int ) {
				Vector_iterator	tmp = *this;

				++(*this);
				return (tmp);
			};

			Vector_iterator	&operator+=( difference_type n ) {
				_it += n;
				return (*this);
			};

			Vector_iterator	&operator-( difference_type n ) const {
				Vector_iterator	tmp(*this);

				return (tmp -= n);
			};

			Vector_iterator	&operator--() {
				_it--;
				return (*this);
			};

			Vector_iterator	operator--( int ) {
				Vector_iterator	tmp = *this;

				--(*this);
				return (tmp);
			};

			Vector_iterator	&operator-=( difference_type n ) {
				_it -= n;
				return (*this);
			};

			pointer			operator->() const {
				return (_it);
			};

			reference		operator[] (difference_type n) const {
				return *(operator+(n));
			};

			template <class iter>
				friend bool operator==(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
			template <class iter>
				friend bool operator!=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
			template <class iter>
				friend bool operator<(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
			template <class iter>
				friend bool operator<=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
			template <class iter>
				friend bool operator>(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
			template <class iter>
				friend bool operator>=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs);
	};

	template <class iter>
		bool	operator==(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (lhs._it == rhs._it)
				return true;
			return false;
		}
	template <class iter>
		bool	operator!=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (!(lhs._it == rhs._it))
				return true;
			return false;
		}
	template <class iter>
		bool	operator<(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (lhs._it < rhs._it)
				return true;
			return false;
		}
	template <class iter>
		bool	operator<=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (!(lhs._it > rhs._it))
				return true;
			return false;
		}
	template <class iter>
		bool	operator>(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (lhs._it > rhs._it)
				return true;
			return false;
		}
	template <class iter>
		bool	operator>=(const Vector_iterator<iter> &lhs, const Vector_iterator<iter> &rhs) {
			if (!(lhs._it < rhs._it))
				return true;
			return false;
		}
}


#endif
