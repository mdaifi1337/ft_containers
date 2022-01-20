/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:38:43 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/20 13:54:28 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP
#include "Iterator_traits.hpp"

namespace ft
{
	template< class Iterator >
		class reverse_iterator : public iterator <
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference>
		{
			private:
				Iterator	_it;

			public:
				typedef Iterator												iterator_type;
				typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
				typedef typename iterator_traits<Iterator>::difference_type		difference_type;
				typedef typename iterator_traits<Iterator>::pointer				pointer;
				typedef typename iterator_traits<Iterator>::reference			reference;

				reverse_iterator() : _it(nullptr) {};
				explicit reverse_iterator( iterator_type it) {
					_it = it;
				};

				template<class iter>
					reverse_iterator(const reverse_iterator<iter> &it) {
					_it = it._it - 1;
				};

				~reverse_iterator() {};

				iterator_type	base() const
				{
					return (_it + 1);
				};

				reference		&operator*() const {
					reverse_iterator	revit = *this;
					return (*(revit._it));
				};
				
				reverse_iterator &operator+(difference_type n) const
				{
					reverse_iterator	revit(*this);

					return (revit += n);
				};

				reverse_iterator &operator++()
				{
					_it--;
					return (*this);
				};

				reverse_iterator operator++(int)
				{
					reverse_iterator	revit(*this);

					++(*this);
					return (revit);
				};

				reverse_iterator &operator+=(difference_type n)
				{
					_it -= n;
					return (*this);
				};

				reverse_iterator &operator-(difference_type n)
				{
					reverse_iterator	revit;

					return (revit -= n);
				};

				reverse_iterator &operator--()
				{
					_it++;
					return (*this);
				};

				reverse_iterator operator--(int)
				{
					reverse_iterator	revit(*this);

					--(*this);
					return (revit);
				};

				reverse_iterator &operator-=(difference_type n)
				{
					_it += n;
					return (*this);
				};

				pointer			operator->() const
				{
					return (&operator*());
				};

				reference		operator[] (difference_type n) const
				{
					return (*(base() - 1));
				};

				template <class iter>
					friend bool operator==(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class iter>
					friend bool operator!=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class iter>
					friend bool operator<(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class iter>
					friend bool operator<=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class iter>
					friend bool operator>(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class iter>
					friend bool operator>=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs);
				template <class Iter>
  					friend typename reverse_iterator<Iter>::difference_type operator- (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs);
		};

		template <class iter>
			bool	operator==(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (lhs.base() == rhs.base())
					return true;
				return false;
			}
		template <class iter>
			bool	operator!=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (!(lhs.base() == rhs.base()))
					return true;
				return false;
			}
		template <class iter>
			bool	operator<(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (lhs.base() < rhs.base())
					return true;
				return false;
			}
		template <class iter>
			bool	operator<=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (!(lhs.base() > rhs.base()))
					return true;
				return false;
			}
		template <class iter>
			bool	operator>(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (lhs.base() > rhs.base())
					return true;
				return false;
			}
		template <class iter>
			bool	operator>=(const reverse_iterator<iter> &lhs, const reverse_iterator<iter> &rhs) {
				if (!(lhs.base() < rhs.base()))
					return true;
				return false;
			}
		template <class Iter>
			typename reverse_iterator<Iter>::difference_type operator- (const reverse_iterator<Iter>& lhs, const reverse_iterator<Iter>& rhs)
			{
				return (rhs.base() - lhs.base());
			}
		template <class Iterator>
			reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it)
			{
				return (rev_it + n);
			};
}


#endif