#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include "pair.hpp"
#include <unistd.h>

namespace ft
{
	template <class value_type>
	struct Node
	{
		int			height;
		Node		*parent;
		Node		*left;
		Node		*right;
		value_type	value;

		Node() {};
		Node(value_type val) : value(val) {};
	};

	template <class value_type>
	void printHelper(Node<value_type> *root, int space) {
		// print the tree structure on the screen
		if (root != nullptr) {
			// std::cout <<
			space += 10;
			printHelper(root->right, space);
			// sleep(1);
			std::cout << std::endl;
			for (int i = 10; i < space; i++)
				std::cout << " ";
			std::cout << "[" << root->value.first << ", " << root->value.second << "]" << std::endl;
			printHelper(root->left, space);
		}
	};

	template <class _node>
	_node	*tree_minimum(_node *node)
	{
		_node	*it = node;

		while (it->left != nullptr)
			it = it->left;
		return it;
	}

	template <class _node>
	_node	*tree_maximum(Node<_node> node)
	{
		_node	*it = node;

		while (it->right != nullptr)
			it = it->right;
		return it;
	}

	template <class value_type, class key_type, class Allocator, class Compare>
	class tree
	{
		public:
			typedef Node<value_type>*	NodePtr;
			typedef Allocator			allocator_type;
			typedef Compare				value_compare;

			NodePtr						root;
			value_compare				cmp;

			tree() {
				this->root = nullptr;
			};
			~tree() {
				delete root;
			};

			tree	copy_tree(NodePtr root) {
				NodePtr	node;

				if (root)
				{
					node = newNode(root->value);
					node->parent = root->parent;
					node->height = root->height;
					copy_tree(root->left);
					copy_tree(root->right);
				}
			};

			tree	&operator=(const tree &other) {
				copy_tree(other.root);
				return *this;
			};

			int	height(NodePtr node) {
				if (node == nullptr)
					return 0;
				return node->height;
			}

			int	max(int val1, int val2) {
				return val1 < val2 ? val2 : val1;
			}

			NodePtr	newNode(value_type val) {
				NodePtr	node = new Node<value_type>(val);
				// node->value = val;
				node->left = nullptr;
				node->right = nullptr;
				node->parent = nullptr;
				node->height = 1;
				return node;
			}

			void	insert(value_type value) {
				this->root = insert_node(this->root, value, this->root);
			};

			NodePtr	insert_node(NodePtr _root, value_type value, NodePtr parent) {
				NodePtr	node;

				if (_root == nullptr)
				{
					node = newNode(value);
					node->parent = parent;
					if (parent == nullptr)
						this->root = node;
					else if (cmp(node->value.first, parent->value.first))
						parent->left = node;
					else
						parent->right = node;
					return node;
				}
				if (cmp(value.first, _root->value.first))
					_root->left = insert_node(_root->left, value, _root);
				else if (!cmp(value.first, _root->value.first) && value.first != _root->value.first)
					_root->right = insert_node(_root->right, value, _root);
				else
					return _root;

				_root->height = 1 + max(height(_root->left), height(_root->right));
				
				int balance = getBalance(_root);

				// Left Left Case
				if (balance > 1 && cmp(value.first, _root->left->value.first))
					return right_rotate(_root);
				// Right Right Case
				if (balance < -1 && !cmp(value.first, _root->right->value.first))
					return left_rotate(_root);
				// Left Right Case
				if (balance > 1 && !cmp(value.first, _root->left->value.first))
				{
					_root->left = left_rotate(_root->left);
					return right_rotate(_root);
				}
				// Right Left Case
				if (balance < -1 && cmp(value.first, _root->right->value.first))
				{
					_root->right = right_rotate(_root->right);
					return left_rotate(_root);
				}
				return _root;
			};

			NodePtr	deleteNode(NodePtr node, key_type key) {
				NodePtr	tmp;

				if (node == nullptr)
					return node; // return current node
				if (cmp(key, node->value.first))
					node->left = deleteNode(node->left, key);
				else if (!cmp(key, node->value.first) && key != node->value.first)
					node->right = deleteNode(node->right, key);
				else
				{
					if (node->left == nullptr) // case 2 : Node has either left or right child
					{
						tmp = node->right;
						if (node->right)
							node->right->parent = node->parent;
						delete node;
						return tmp;
					}
					else if (node->right == nullptr)
					{
						tmp = node->left;
						if (node->left)
							node->left->parent = node->parent;
						delete node;
						return tmp;
					}
					else // case 3 : Node has 2 children : We need to find the minimum node in the the node's right subtree
					{
						NodePtr	right;

						tmp = tree_minimum(node->right);
						std::cout << "min : " << tmp->value.second << std::endl;
						right = tmp->right;
						tmp->left = node->left;
						if (tmp->parent && tmp->parent->value.first != root->value.first)
						{
							tmp->right = node->right;
							node->right->parent = tmp;
						}
						if (tmp->left)
							tmp->left->parent = tmp;
						if (tmp->parent && tmp->parent->value.first != root->value.first)
						{
							if (right)
								right->parent = node->right;
							tmp->parent->left = right;
						}
						tmp->parent = node->parent;
						delete node;
					}
				}
				if (node == nullptr)
					return node;
				tmp->height = 1 + max(height(tmp->left), height(tmp->right));

				int balance = getBalance(tmp);

				// Left Left Case
				if (balance > 1 && getBalance(tmp) >= 0)
					return right_rotate(tmp);
				// Left Right Case
				if (balance > 1 && getBalance(tmp->left) < 0)
				{
					tmp->left = left_rotate(tmp->left);
					return right_rotate(tmp);
				}
				// Right Right Case
				if (balance < -1 && getBalance(tmp) <= 0)
					return left_rotate(tmp);
				// Right Left Case
				if (balance < -1 && getBalance(tmp->right) > 0)
				{
					tmp->right = right_rotate(tmp->right);
					return left_rotate(tmp);
				}
				return tmp;
			};

			void	erase(key_type key) {
				this->root = this->deleteNode(this->root, key);
			};

			NodePtr	successor(NodePtr node) {
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

			NodePtr	predecessor(NodePtr node) {
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

			NodePtr	left_rotate(NodePtr node) {
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

				node->height = max(height(node->left), height(node->right)) + 1;
				tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
				return (tmp);
			}

			NodePtr	right_rotate(NodePtr node) {
				NodePtr	tmp = node->left;

				node->left = tmp->right;
				if (tmp->right != nullptr)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == nullptr)
					this->root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;

				node->height = max(height(node->left), height(node->right)) + 1;
				tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
				return (tmp);
			}

			int	getBalance(NodePtr node) {
				if (node == nullptr)
					return 0;
				return height(node->left) - height(node->right);
			}

			bool	find(key_type key) {
				NodePtr	it = this->root;

				while (it != nullptr)
				{
					if (cmp(key, it->value.first))
						it = it->left;
					if (!cmp(key, it->value.first) && key != it->value.first)
						it = it->right;
					else
						return true;
				}
				return false;
			}

			NodePtr	tree_minimum() {
				NodePtr	it = root;

				while (it->left != nullptr)
					it = it->left;
				return it;
			}

			NodePtr	tree_maximum() {
				NodePtr	it = root;

				while (it->right != nullptr)
					it = it->right;
				return it;
			}
	};
	template <class NodePtr>
	NodePtr	successor(NodePtr *node)
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

	template <class NodePtr>
	NodePtr	predecessor(NodePtr *node)
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

	template <class Iterator, class Node>
	class map_iterator
	{
		public:
			typedef	Node		nodePtr;
			typedef	Iterator*	pointer;
			typedef	Iterator&	reference;

			map_iterator() : _it() {};

			map_iterator(nodePtr it) : _it(it) {};

			template <class iter, class node>
			map_iterator (const map_iterator<iter, node> &it) {
				_it = it.base();
			};

			map_iterator	&operator=(const map_iterator &it) {
				_it = it.base();
			};

			nodePtr	base() const {
				return _it;
			};

			reference	&operator*() const {
				return (_it->value);
			};

			pointer		operator->() const {
				return (&_it->value);
			};

			map_iterator	&operator++() {
				_it = successor(_it);
				return (*this);
			}

			map_iterator	operator++(int) {
				map_iterator tmp = *this;

				++(*this);
				return tmp;
			};

			map_iterator	&operator--() {
				_it = predecessor(_it);
				return (*this);
			}

			map_iterator	operator--(int) {
				map_iterator tmp = *this;

				--(*this);
				return tmp;
			};

			~map_iterator() {};

		private:
			nodePtr	_it;
	};

	template <class iterator>
	class map_reverse_iterator
	{
		public:
			typedef	iterator*	pointer;
			typedef	iterator&	reference;

			map_reverse_iterator() : _it() {};

			template <class iter>
			map_reverse_iterator(const map_reverse_iterator<iter> &other) {
				_it = --other.base();
			};

			map_reverse_iterator	&operator=(const map_reverse_iterator &other) {
				_it = other.base();
			};

			iterator	base() const {
				return ++_it;
			};

			reference	&operator*() const {
				return _it->value;
			};

			pointer	operator->() const {
				return &(operator*());
			};

			map_reverse_iterator	&operator++()
			{
				_it--;
				return *this;
			};

			map_reverse_iterator	&operator++(int) {
				map_reverse_iterator	tmp = *this;

				++(*this);
				return *this;
			};

			map_reverse_iterator	&operator--()
			{
				_it++;
				return *this;
			};

			map_reverse_iterator	&operator--(int) {
				map_reverse_iterator	tmp = *this;

				--(*this);
				return *this;
			};

			~map_reverse_iterator() {};

		private:
			iterator	_it;
	};

	template < class Key,                                     // map::key_type
           	class T,                                       // map::mapped_type
           	class Compare = std::less<Key>,                     // map::key_compare
           	class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           	>
	class map
	{
		private:
			typedef Key											key_type;
			typedef Compare										key_compare;

			template <class value_type, class key_type>
			class my_val_comp // : public std::binary_function<value_type, value_type, bool> 
			{
				public:
					key_compare	cmp;
					my_val_comp() {};
					~my_val_comp() {};
					bool operator() (const value_type& x, const value_type& y) const
					{
						return cmp(x.first, y.first);
					}
					bool operator() (const key_type& x, const value_type& y) const
					{
						return cmp(x, y.first);
					}
					bool operator() (const value_type& x, const key_type& y) const
					{
						return cmp(x.first, y);
					}
					bool operator() (const key_type& x, const key_type& y) const
					{
						return cmp(x, y);
					}
			};

			typedef T														mapped_key;
			typedef ft::pair<const key_type, mapped_key>					value_type;
			typedef Node<value_type>*										nodePtr;
			typedef my_val_comp<value_type, key_type>						value_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef ft::map_iterator<value_type, nodePtr>					iterator;
			typedef ft::map_iterator<const value_type, nodePtr>				const_iterator;
			typedef ft::map_reverse_iterator<iterator>						reverse_iterator;
			typedef ft::map_reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;
			typedef tree<value_type, key_type, allocator_type, key_compare>	tree;


		public:
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0)
			{};

			iterator	begin() {
				return (iterator(_root.tree_minimum()));
			}

			const_iterator	begin() const {
				return (const_iterator(_root.tree_minimum()));
			}

			iterator	end() {
				return (++iterator(_root.tree_maximum()));
			}

			const_iterator	end() const {
				return (++const_iterator(_root.tree_maximum()));
			}
			
			reverse_iterator	rbegin() {
				return (reverse_iterator(_root.tree_maximum()));
			}
			
			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(_root.tree_maximum()));
			}

			reverse_iterator	rend() {
				return (++reverse_iterator(_root.tree_minimum));
			}

			const_reverse_iterator	rend() const {
				return (++const_reverse_iterator(_root.tree_minimum));
			}

			bool	empty() const {
				if (_size == 0)
					return true;
				return false;
			};

			size_type	size() {
				return _size;
			}

			void	insert(const value_type &val)
			{
				if (count(val.first))
					return (ft::make_pair(val.first, 0));
				_root.insert(val);
				_size++;
			};

			void	erase(const key_type &val)
			{
				_root.erase(val);
				_size--;
			};

			size_type	count(const key_type &key) const
			{
				if (_size == 0 || _root.find(key) == false)
					return 0;
				return 1;
			};

			void	print_tree(int space)
			{
				printHelper(_root.root, space);
			};

		private:
			tree			_root;
			allocator_type	_alloc;
			size_type		_size;
	};
}

#endif