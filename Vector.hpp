/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:00:12 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/16 15:29:08 by mdaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "Iterator.hpp"
# include "type_traits.hpp"

namespace ft
{
	template< class T , class Alloc = std::allocator<T> > 
	class Vector
	{
		public :
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef 		 ft::Vector_iterator<pointer>			iterator;
			typedef 		 ft::Vector_iterator<const_pointer>		const_iterator;
			// typedef 		 ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef 		 ft::reverse_iterator<const iterator>	const_reverse_iterator;
			typedef 		 ptrdiff_t								difference_type;
			typedef 		 size_t									size_type;

		private:

			pointer			_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			
		public:
			explicit Vector (const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc) {};
			explicit Vector (size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type()) : _size(0), _capacity(0), _alloc(alloc)
					{
						this->assign(n, val);
					};
			// template <class InputIterator>
			// Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {};
			Vector (const Vector& x) {};
			~Vector() {};

			// RECHECK THIS
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				InputIterator	it;
				size_type		size = 0;

				it = first;
				while (it != last)
				{
					size++;
					it++;
				}
				if (size > _capacity)
				{
					if (_capacity)
					{
						for (InputIterator it = this->begin(); it != this->end(); it++)
							_alloc.destroy(&(*it));
						_alloc.deallocate(_data, _capacity);
					}
					_capacity = size;
					_data = _alloc.allocate(_capacity, 0);
					for (InputIterator it = this->begin(); it != this->end(); it++)
						_alloc.construct(&(*it), 0);
				}
				for (InputIterator it = this->begin(); first != last; it++)
					*it = *(first++);
				// while (first != last) {
				// 	push_back(*first);
				// 	first++;
				// }
				_size = size;
			};

			void	assign(size_type n, const value_type& val) {
				if (n > _capacity) {
					Vector	tmp;

					tmp._data = _alloc.allocate(n, 0);
					tmp._capacity = n;
					tmp._size = n;
					for (iterator it = tmp.begin(); it != tmp.end(); it++)
						_alloc.construct(&(*it), val);
					// std::cout << "size : " << _size << std::endl << std::endl;
					if (_size > 0)
						for (iterator it = this->begin(); it != this->end(); it++)
							_alloc.destroy(&(*it));
					_data = tmp._data;
					_capacity = n;
					_size = n;
				}
				else {
					_size = n;
					for (iterator it = this->begin(); it != this->end(); it++)
						_alloc.destroy(&(*it));
					for (iterator it = this->begin(); it != this->end(); it++)
						_alloc.construct(&(*it), val);
				}
			};

			iterator	begin() {
				return (iterator(_data));
			};

			const_iterator	begin() const {
				return (iterator(_data));
			};

			iterator	end() {
				return (iterator(_data + _size));
			};

			const_iterator	end() const {
				return (iterator(_data + _size));
			};

			// reverse_iterator	rbegin() {
			// 	return (&_data[_size]);
			// };

			// const_reverse_iterator	rbegin() const {
			// 	return (&_data[_size]);
			// };

			// reverse_iterator	rend() {
			// 	return ((&_data[0]) + 1);
			// };

			// const_reverse_iterator	rend() const {
			// 	return ((&_data[0]) + 1);
			// };

			size_type	size() const {
				return (_size);
			};

			size_type	max_size() const {
				return (_alloc.max_size());
			};

			void	resize(size_type n, value_type val = value_type())
			{
				if (n < _size) {
					// deallocate ?
					for (iterator it = this->begin(); it != this->end(); it++)
						_alloc.destroy(&(*it)); //erase
					_size = n;
				}
				else if (n > _size && n < _capacity) {
					for (size_type i = _size; i < n; i++)
						_data[i] = val; //insert
					_size = n;
				}
				else if (n > _capacity) {
					//reallocate new data block
					pointer	newData;

					newData = _alloc.allocate(n);
					for (iterator it = this->begin(); it != this->end(); it++)
						_alloc.construct(newData, 0);
					if (_size > 0)
					{
						for (size_type i = 0; i < _size; i++)
							newData[i] = _data[i];
						_alloc.deallocate(_data, _capacity);
						for (iterator it = this->begin(); it != this->end(); it++)
							_alloc.destroy(&(*it)); //erase
					}
					_data = newData;
					_capacity = n;
				}
			};

			size_type	capacity() const {
				return (_capacity);
			};

			bool	empty() const {
				if (_size == 0)
					return (true);
				return (false);
			};

			void	reserve(size_type n) {
				if (n > _capacity) {
					pointer	newData;

					newData = _alloc.allocate(n, 0);
					_alloc.construct(newData, 0);
					if (_size > 0)
					{
						for (size_type i = 0; i < _size; i++)
							newData[i] = _data[i];
						_alloc.deallocate(_data, _capacity);
						for (iterator it = this->begin(); it != this->end(); it++)
							_alloc.destroy(&(*it));
					}
					_data = newData;
					_capacity = n;
				}
			};

			reference		operator[](size_type n) {
				return (_data[n]);
			};

			const_reference	operator[](size_type n) const {
				return (_data[n]);
			};

			reference		at(size_type n) {
				try {
					if (n < 0 || n > _capacity)
						throw std::out_of_range("");
					return (_data[n]);
				}
				catch(const std::exception& e) {
					std::cerr << e.what() << '\n';
				}
			};

			const_reference	at(size_type n) const {
				try {
					if (n < 0 || n > _capacity)
						throw std::out_of_range("");
					return (_data[n]);
				}
				catch(const std::exception& e) {
					std::cerr << e.what() << '\n';
				}
			};

			reference		front() {
				return (_data[0]);
			};

			const_reference	front() const {
				return (_data[0]);
			};

			reference		back() {
				return (_data[_size - 1]);
			};

			const_reference	back() const {
				return (_data[_size - 1]);
			};

			void	push_back(const value_type &val) {
				if (_size == _capacity)
				{
					if (_capacity == 0)
						this->resize(1);
					else
						this->resize(_capacity * 2);
				}
				_data[_size++] = val;
			};

			void	pop_back() {
				_alloc.destroy(_data[_size - 1]);
				_size--;
			};

			iterator	insert(iterator position, const value_type& val) {
				if (_size == _capacity)
					this->resize(_capacity * 2);
				_size++;
				iterator it;
				for (it = position; it != this->end(); it++)
					*(it + 1) = *it;
				*it = val;
				return (it);
			};

			void		insert(iterator position, size_type n, const value_type &val){
				if (_size + n >= _capacity)
					_capacity * 2 < n ? this->resize(_capacity + n) : this->resize(_capacity * 2);
				_capacity = _capacity * 2 < n ? _capacity + n : _capacity * 2;
				for (size_type i = _size; i < n; i++)
					_data[i] = val;
				_size += n;
			};

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {
				difference_type	size;
				size = last - first;
				if (_size + size == _capacity)
					_capacity * 2 < size ? this->resize(_capacity + size) : this->resize(_capacity * 2);
				_capacity = _capacity * 2 < size ? _capacity + size : _capacity * 2;
				for (size_type i = _size; first != last; first++, i++)
					_data[i] = *first;
				_size += size;
			};

			iterator	erase(iterator position) {
				for (iterator it = position; it != this->end() - 1; it++)
					*it = *(it + 1);
				_alloc.destroy(this->end() - 1);
				_size--;
				if (position == this->end() - 1)
					return this->end();
				return position + 1;
			};

			iterator	erase(iterator first, iterator last) {
				difference_type	size = last - first;

				for (iterator it = first; it + size != this->end() - 1 && it != last - 1; it++)
					*it = *(it + size);
				for (; last != this->end(); last++)
					_alloc.destroy((last));
				return (last);
			};

			void	swap(Vector &x)
			{
				// to re-check
				Vector	*tmp;

				tmp = this;
				this = &x;
				x = *tmp;
			}
	};
}

#endif
