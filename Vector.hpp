/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaifi <mdaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:00:12 by mdaifi            #+#    #+#             */
/*   Updated: 2022/01/19 10:13:26 by mdaifi           ###   ########.fr       */
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
			// Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					// typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {};
			Vector (const Vector& x) {};
			~Vector() {};

			// RECHECK THIS
			template <class InputIterator>
			void	assign(InputIterator first, InputIterator last,
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				difference_type	size = last - first;

				if (size > _capacity)
				{
					if (_capacity)
					{
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&(_data[i]));
						_alloc.deallocate(_data, _capacity);
					}
					_capacity = size;
					_data = _alloc.allocate(_capacity, 0);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&(_data[i]), 0);
				}
				for (size_type i = 0; first != last; i++)
					_data[i] = *(first++);
				_size = size;
			};

			void	assign(size_type n, const value_type& val) {
				if (n > _capacity) {
					Vector	tmp;

					tmp._data = _alloc.allocate(n, 0);
					tmp._capacity = n;
					tmp._size = n;
					for (size_type i = 0; i < tmp.size(); i++)
						_alloc.construct(&(tmp[i]), val);
					if (_size > 0)
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&(_data[i]));
					_data = tmp._data;
					_capacity = n;
					_size = n;
				}
				else {
					_size = n;
					for (size_type i = 0; i < n; i++)
						_alloc.destroy(&(_data[i]));
					for (size_type i = 0; i < n; i++)
						_alloc.construct(&(_data[i]), val);
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
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(&(_data[i])); //erase
				}
				else if (n > _size && n <= _capacity) {
					for (size_type i = _size; i < n; i++)
					{
						_alloc.destroy(_data + i); //erase
						_alloc.construct(_data + i, val);
					}
				}
				else if (n > _capacity) {
					pointer	tmp = nullptr;

					if (_size > 0)
					{
						tmp = _data;
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&(_data[i])); //erase
					}
					if (_capacity)
						_data = _alloc.allocate(_capacity * 2, 0);
					else
						_data = _alloc.allocate(n, 0);
					if (_size)
						_alloc.deallocate(tmp, _capacity);
					if (tmp)
						for (size_type i = 0; i < _size; i++)
							_data[i] = tmp[i];
					for (size_type i = _size; i < n; i++)
						_alloc.construct(&_data[i], val);
					_capacity = _capacity == 0 ? n : _capacity * 2;
				}
				_size = n;
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

					if (_capacity)
						newData = _alloc.allocate(_capacity * 2, 0);
					else
						newData = _alloc.allocate(n, 0);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(newData, 0);
					if (_size > 0)
					{
						for (size_type i = 0; i < _size; i++)
							newData[i] = _data[i];
						_alloc.deallocate(_data, _capacity);
						for (size_type i = 0; i < _size; i++)
							_alloc.destroy(&(_data[i]));
					}
					_data = newData;
					_capacity = _capacity == 0 ? n : _capacity * 2;
				}
			};

			reference		operator[](size_type n) {
				return (_data[n]);
			};

			const_reference	operator[](size_type n) const {
				return (_data[n]);
			};

			reference		at(size_type n) {
				if (n < 0 || n >= _size)
					throw std::out_of_range("out of range exception");
				return (_data[n]);
			};

			const_reference	at(size_type n) const {
				if (n < 0 || n >= _size)
					throw std::out_of_range("");
				return (_data[n]);
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
				if (_size >= _capacity)
				{
					if (_capacity == 0)
						this->reserve(1);
					else
						this->reserve(_capacity * 2);
				}
				_data[_size++] = val;
			};

			void	pop_back() {
				_alloc.destroy(&_data[_size - 1]);
				_size--;
			};

			iterator	insert(iterator position, const value_type& val) {
				difference_type	pos = position - this->begin();
				if (_size == _capacity)
					this->reserve(_capacity * 2);
				for (size_type i = _size - 1; i > pos ; i--)
					_data[i] = _data[i - 1];
				_alloc.destroy(&(*position));
				_alloc.construct(&(*position), val);
				_size++;
				return (position);
			};

			void		insert(iterator position, size_type n, const value_type &val){
				difference_type pos = position - this->begin();
				difference_type old_end = (this->end() - this->begin()) - 1;
				
				if (_size + n >= _capacity)
					_capacity * 2 < n ? this->reserve(_capacity + n) : this->reserve(_capacity * 2);
				_size += n;
				iterator it = this->begin() + pos;
				iterator it_end = this->begin() + old_end;
				while (it_end >= it)
				{
					*(it_end + n) = *(it_end);
					it_end--;
				}
				it_end = this->begin() + pos + n;
				it = this->begin() + pos;
				while (it != it_end)
				{
					_alloc.destroy(&(*it));
					_alloc.construct(&(*it), val);
					it++;
				}
			};

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) {
				difference_type	size = last - first;
				difference_type	pos = position - this->begin();
				difference_type old_end = (this->end() - this->begin()) - 1;

				if (_size + size >= _capacity)
					_capacity * 2 < size ? this->reserve(_capacity + size) : this->reserve(_capacity * 2);
				iterator it = this->begin() + pos;
				iterator it_end = this->begin() + old_end;
				while (it <= it_end)
				{
					*(it_end + size) = *(it_end);
					it_end--;
				}
				for (size_type i = pos; first != last; first++, i++)
					_data[i] = *first;
				_size += size;
			};

			iterator	erase(iterator position) {
				difference_type	pos = position - this->begin();

				for (size_type i = pos; i < _size - 1; i++)
					_data[i] = _data[i + 1];
				_alloc.destroy(&(_data[_size - 1]));
				_size--;
				if (position == this->end())
					return this->end();
				return position + 1;
			};

			iterator	erase(iterator first, iterator last) {
				difference_type	size = last - first;
				difference_type	pos = first - this->begin();

				for (size_type i = pos; i < size; i++)
					_data[i] = _data[i + size];
				for (; last != this->end(); last++)
					_alloc.destroy(&(*last));
				_size -= size;
				return (last);
			};

			void	swap(Vector &x)
			{
				// to re-check
				Vector	tmp;

				tmp = *this;
				*this = x;
				x = tmp;
			}
	};
}

#endif
