#ifndef STACK_HPP
#define STACK_HPP
#include "Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> > 
	class stack
	{

		public :
			typedef Container                                container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::reference       reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type       size_type;

			explicit stack (const container_type& ctnr = container_type()) {};
			~stack() {};

		protected :
			container_type	c;

		public:
			bool	empty() const
			{
				if (c.empty() == true)
					return true;
				return (false);
			};

			size_type	size() const
			{
				return (c.size());
			};

			value_type	&top()
			{
				return (c.back());
			};

			const value_type	&top() const
			{
				return (c.back());
			};

			void	push(const value_type &val)
			{
				c.push_back(val);
			};

			void	pop()
			{
				c.pop_back();
			};

			template <class Type, class Ctnr>
			friend bool operator== (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

			template <class Type, class Ctnr>
			friend bool operator!= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

			template <class Type, class Ctnr>
			friend bool operator<  (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

			template <class Type, class Ctnr>
			friend bool operator<= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

			template <class Type, class Ctnr>
			friend bool operator>  (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

			template <class Type, class Ctnr>
			friend bool operator>= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs);

	};
	
	template <class Type, class Ctnr>
	bool operator== (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c == rhs.c)
			return (true);
		return (false);
	}

	template <class Type, class Ctnr>
	bool operator!= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c != rhs.c)
			return (true);
		return (false);
	}

	template <class Type, class Ctnr>
	bool operator< (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c < rhs.c)
			return (true);
		return (false);
	}

	template <class Type, class Ctnr>
	bool operator<= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c <= rhs.c)
			return (true);
		return (false);
	}

	template <class Type, class Ctnr>
	bool operator> (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c > rhs.c)
			return (true);
		return (false);
	}

	template <class Type, class Ctnr>
	bool operator>= (const stack<Type,Ctnr>& lhs, const stack<Type,Ctnr>& rhs) {
		if (lhs.c >= rhs.c)
			return (true);
		return (false);
	}
}

#endif