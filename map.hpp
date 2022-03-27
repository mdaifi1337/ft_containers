#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include "pair.hpp"

namespace ft
{
	template <class value_type>
	struct Node
	{
		int			height;
		int			bf;
		Node		*parent;
		Node		*left;
		Node		*right;
		value_type	value;

		Node() {};
	};

	template <class _node>
	Node<_node>	*tree_minimum(Node<_node> node)
	{
		_node	*it = node;

		while (it->left != nullptr)
			it = it->left;
		return it;
	}

	template <class _node>
	Node<_node>	*tree_maximum(Node<_node> node)
	{
		_node	*it = node;

		while (it->right != nullptr)
			it = it->right;
		return it;
	}

	template <class value_type, class key_type, class Allocator, class Compare>
	class tree
	{
		private:
			typedef Node<value_type>*	NodePtr;
			typedef Allocator			allocator_type;
			typedef Compare				value_compare;
			NodePtr	*root;


		tree() {
			this->root = nullptr;
		};
		~tree() {};

		public:
			void	insert(value_type value)
			{
				NodePtr	node = new Node<value_type>;
				NodePtr	parent = nullptr;
				NodePtr	it;

				node->value = value;
				node->left = nullptr;
				node->right = nullptr;
				node->parent = nullptr;
				node->bf = 0;
				it = this->root;
				while (it != nullptr)
				{
					parent = it;
					if (value == it->value)
						return ; // return current node
					if (node->value < it->value)
						it = it->left;
					else
						it = it->right;
				}

				node->parent = parent;
				if (parent == nullptr)
					this->root = node;
				else if (node->value < parent->value)
					parent->left = node;
				else
					parent->right = node;
				updateBalance(node);
			};

			NodePtr	deleteNode(NodePtr node, key_type key)
			{
				NodePtr	tmp;

				if (node == nullptr)
					return ; // return current node
				if (key < node->first)
					node->left = deleteNode(node->left, key);
				else if (key > node->first)
					node->right = deleteNode(node->right, key);
				else
				{
					if (node->left == nullptr) // case 2 : Node has either left or right child
					{
						tmp = node->right;
						delete node;
						return tmp;
					}
					else if (node->right == nullptr)
					{
						tmp = node->left;
						delete node;
						return tmp;
					}
					else // case 3 : Node has 2 children : We need to find the minimum node in the the node's right subtree
					{
						tmp = tree_minimum(node->right);
						node->value.second = tmp->value.second; // Not sure it should be value or value.second (aka should the key change or not)
						node->right = deleteNode(node->right, tmp->value.first);
					}
				}
				return node;
			};

			NodePtr	successor(NodePtr node)
			{
				NodePtr	tmp;

				if (node->right != nullptr)
					return (tree_minimum(node->right));
				tmp = node->parent;
				while (tmp != nullptr && node == tmp->right)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}

			NodePtr	predecessor(NodePtr node)
			{
				NodePtr	tmp;

				if (node->left != nullptr)
					return (tree_maximum(node->left));
				tmp = node->parent;
				while (tmp != nullptr && node == tmp->left)
				{
					node = tmp;
					tmp = tmp->parent;
				}
				return (tmp);
			}

			void	left_rotate(NodePtr node)
			{
				NodePtr	tmp = node->right;

				node->right = tmp->left;
				if (tmp->left != nullptr)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == nullptr)
					this->root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;

				node->bf -= 1 - max(0, tmp->bf); // still need to understand why this is like this
				node->bf -= 1 + min(0, node->bf);
			}

			void	right_rotate(NodePtr node)
			{
				NodePtr	tmp = node->left;

				node->left = tmp->right;
				if (tmp->right != nullptr)
					tmp->right->parent = node;
				node->parent = tmp->parent;
				if (node->parent == nullptr)
					this->root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;

				node->bf += 1 - min(0, tmp->bf);
				node->bf += 1 + max(0, node->bf);
			}

			void	updateBalance(NodePtr node)
			{
				if (node->bf < -1 || node->bf > 1)
				{
					rebalance(node);
					return ;
				}
				if (node->parent != nullptr)
				{
					if (node == node->parent->left)
						node->parent->bf -= 1;
					if (node == node->parent->right)
						node->parent->bf += 1;
					if (node->parent->bf != 0)
						updateBalance(node->parent);
				}
			}

			void	rebalance(NodePtr node)
			{
				if (node->bf > 0)
				{
					if (node->right->bf < 0)
					{
						right_rotate(node->right);
						left_rotate(node);
					}
					else
						left_rotate(node);
				}
				else if (node->bf < 0)
				{
					if (node->left->bf > 0)
					{
						left_rotate(node->left);
						right_rotate(node);
					}
					else
						right_rotate(node);
				}
			}
	};

	// template < class Key,                                     // map::key_type
    //        	class T,                                       // map::mapped_type
    //        	class Compare = std::less<Key>,                     // map::key_compare
    //        	class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
    //        	>
	// class map
	// {
	// 	private:

	// 		typedef Key											key_type;
	// 		typedef T											mapped_key;
	// 		typedef ft::pair<const key_type, mapped_key>		value_type;
	// 		typedef Compare										key_compare;
	// 		typedef Alloc										allocator_type;
	// 		typedef typename allocator_type::reference			reference;
	// 		typedef typename allocator_type::const_reference	const_reference;
	// 		typedef typename allocator_type::pointer			pointer;
	// 		typedef typename allocator_type::const_pointer		const_pointer;
	// 		// typedef ft::map_iterator<pointer>					iterator;
	// 		// typedef ft::map_iterator<const_pointer>				const_iterator;
	// 		// typedef ft::map_reverse_iterator<pointer>			reverse_iterator;
	// 		// typedef ft::mapreverse__iterator<const_pointer>		const_reverse_iterator;
	// 		typedef ptrdiff_t									difference_type;
	// 		typedef size_t										size_type;


	// 	public:
	// 		class value_compare : public std::binary_function<value_type, value_type, bool> {};
	// 		// struct BST	tree;
	// 		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _root(nullptr), _comp(comp)
	// 		{};

	// 		void	insert(const value_type &val)
	// 		{
	// 			Node	*node;
	// 			Node	*parent = nullptr;
	// 			Node	*it;

	// 			node = _alloc.allocate(1);
	// 			node->value = val;
	// 			node->left = nullptr;
	// 			node->right = nullptr;
	// 			node->parent = nullptr;
	// 			it = this->_root;
	// 			while (it != nullptr)
	// 			{
	// 				parent = it;
	// 				if (node->value.first < it->value.first)
	// 					it = it->left;
	// 				else if (node->value.first > it->value.first)
	// 					it = it->right;
	// 				else if (node->value.first == it->value.first)
	// 					return ;
	// 			}

	// 			node->parent = parent;
	// 			if (parent == nullptr)
	// 				this->_root = node;
	// 			else if (node->value.first < parent->value.first)
	// 				parent->left = node;
	// 			else
	// 				parent->right = node;
	// 		};

	// 	private:
	// 		Node			*_root;
	// 		allocator_type	_alloc;
	// 		key_compare		_comp;
	// 		size_type		_size;
	// };
}

#endif