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
			space += 10;
			printHelper(root->right, space);
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
	_node	*tree_maximum(_node *node)
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
			typedef Compare				key_compare;

			NodePtr						root;
			key_compare					cmp;

			tree() {
				this->root = nullptr;
			};
			~tree() {
				clear();
			};

			NodePtr	copy_tree(NodePtr root) {
				NodePtr	node;

				if (root)
				{
					node = newNode(root->value);
					node->parent = root->parent;
					node->height = root->height;
					if (root->left)
						node->left = copy_tree(root->left);
					if (root->right)
						node->right = copy_tree(root->right);
				}
				return node;
			};

			tree	&operator=(const tree &other) {
				this->root = copy_tree(other.root);
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
				NodePtr	prev = node;

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
						right = tmp->right;
						tmp->left = node->left;
						if (tmp->left)
							tmp->left->parent = tmp;
						if (tmp->parent && tmp->parent->value.first != prev->value.first)
						{
							tmp->right = node->right;
							tmp->parent->parent = tmp;
							if (right)
								right->parent = node->right;
							tmp->parent->left = right;
						}
						tmp->parent = node->parent;
						delete node;
						return tmp;
					}
				}
				if (node == nullptr)
					return node;
				node->height = 1 + max(height(node->left), height(node->right));

				int balance = getBalance(node);

				// Left Left Case
				if (balance > 1 && getBalance(node) >= 0)
					return right_rotate(node);
				// Left Right Case
				if (balance > 1 && getBalance(node->left) < 0)
				{
					node->left = left_rotate(node->left);
					return right_rotate(node);
				}
				// Right Right Case
				if (balance < -1 && getBalance(node) <= 0)
					return left_rotate(node);
				// Right Left Case
				if (balance < -1 && getBalance(node->right) > 0)
				{
					node->right = right_rotate(node->right);
					return left_rotate(node);
				}
				return node;
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

			NodePtr	find(key_type key) const {
				NodePtr	it = this->root;

				while (it != nullptr)
				{
					if (cmp(key, it->value.first))
						it = it->left;
					else if (!cmp(key, it->value.first) && key != it->value.first)
						it = it->right;
					else
						return it;
				}
				return nullptr;
			}

			NodePtr	tree_min() {
				NodePtr	it = root;

				while (it->left != nullptr)
					it = it->left;
				return it;
			}

			NodePtr	tree_max() {
				NodePtr	it = root;

				while (it->right != nullptr)
					it = it->right;
				return it;
			}

			void	recursive_delete(NodePtr node) {
				if (node)
				{
					recursive_delete(node->left);
					recursive_delete(node->right);
					delete node;
					node = nullptr;
				}
			}

			void	clear() {
				if (root)
					recursive_delete(root);
				root = nullptr;
			}
	};

	template <class NodePtr>
	NodePtr	*successor(NodePtr *node)
	{
		NodePtr	*tmp;
		if (node->right != nullptr)
			return (tree_minimum(node->right));
		tmp = node->parent;
		while (tmp != nullptr && tmp->right && node->value.first == tmp->right->value.first)
		{
			node = tmp;
			tmp = tmp->parent;
		}
		return tmp;
	}

	template <class NodePtr>
	NodePtr	*predecessor(NodePtr *node)
	{
		NodePtr	*tmp;
		if (node->left != nullptr)
			return (tree_maximum(node->left));
		tmp = node->parent;
		while (tmp != nullptr && tmp->left && node->value.first == tmp->left->value.first)
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

			map_iterator(const map_iterator &other) {
				_it = other.base();
			};

			template <class iter>
			map_iterator (const iter &it) {
				_it = it.base();
			};

			map_iterator	&operator=(const map_iterator &it) {
				_it = it.base();
				return *this;
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

			template <class iter, class node>
			friend bool	operator==(const map_iterator<iter, node> &lhs, const map_iterator<iter, node> &rhs) {
				if ((lhs._it) == (rhs._it))
					return true;
				return false;
			}
			template <class iter, class node>
			friend bool	operator!=(const map_iterator<iter, node> &lhs, const map_iterator<iter, node> &rhs) {
				if (!(lhs._it == rhs._it))
					return true;
				return false;
			}

		private:
			nodePtr	_it;
	};

	template <class Iterator>
	class map_reverse_iterator
	{
		public:
			typedef	typename Iterator::pointer		pointer;
			typedef	typename Iterator::reference	reference;

			map_reverse_iterator() : _it() {};

			map_reverse_iterator(Iterator other) : _it(other) {};

			map_reverse_iterator(const map_reverse_iterator &other) {
				_it = other._it;
			};

			map_reverse_iterator	&operator=(const map_reverse_iterator &other) {
				_it = other._it;
				return *this;
			};

			reference	operator*() const {
				return (*_it);
			};

			pointer	operator->() const {
				return &(operator*());
			};

			map_reverse_iterator	&operator++() {
				_it--;
				return *this;
			};

			map_reverse_iterator	operator++(int) {
				map_reverse_iterator	tmp = *this;

				++(*this);
				return tmp;
			};

			map_reverse_iterator	&operator--() {
				_it++;
				return *this;
			};

			map_reverse_iterator	operator--(int) {
				map_reverse_iterator	tmp = *this;

				_it++;
				return tmp;
			};

			~map_reverse_iterator() {};

			template <class iter>
			friend bool	operator==(const map_reverse_iterator<iter> &lhs, const map_reverse_iterator<iter> &rhs) {
				if (*(lhs._it) == *(rhs._it))
					return true;
				return false;
			}
			template <class iter>
			friend bool	operator!=(const map_reverse_iterator<iter> &lhs, const map_reverse_iterator<iter> &rhs) {
				if (!(lhs._it == rhs._it))
					return true;
				return false;
			}

		private:
			Iterator	_it;
	};

	template < class Key,                                     // map::key_type
           	class T,                                       // map::mapped_type
           	class Compare = std::less<Key>,                     // map::key_compare
           	class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           	>
	class map
	{
		public:
			typedef Key											key_type;
			typedef Compare										key_compare;
			template <class value_type, class key_type>
			class my_val_comp // : public std::binary_function<value_type, value_type, bool> 
			{
				public:
					key_compare	cmp;
					my_val_comp() {};
					~my_val_comp() {};
					bool operator() (const value_type& x, const value_type& y) const {
						return cmp(x.first, y.first);
					}
					bool operator() (const key_type& x, const value_type& y) const {
						return cmp(x, y.first);
					}
					bool operator() (const value_type& x, const key_type& y) const {
						return cmp(x.first, y);
					}
					bool operator() (const key_type& x, const key_type& y) const {
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
			typedef map_iterator<value_type, nodePtr>						iterator;
			typedef map_iterator<const value_type, nodePtr>					const_iterator;
			typedef map_reverse_iterator<iterator>							reverse_iterator;
			typedef map_reverse_iterator<const_iterator>					const_reverse_iterator;
			typedef ptrdiff_t												difference_type;
			typedef size_t													size_type;
			typedef tree<value_type, key_type, allocator_type, key_compare>	tree;

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), cmp(comp) {};

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _alloc(alloc), cmp(comp) {
				insert(first, last);
			};

			map(const map &other) {
				*this = other;
			};

			map	&operator=(const map &other) {
				_root = other._root;
				_size = other.size();
				_alloc = other._alloc;
				cmp = other.cmp;
				return *this;
			};

			iterator	begin() {
				return (iterator(_root.tree_min()));
			}

			const_iterator	begin() const {
				return (const_iterator(_root.tree_min()));
			}

			iterator	end() {
				return (++iterator(_root.tree_max()));
			}

			const_iterator	end() const {
				return (++const_iterator(_root.tree_max()));
			}
			
			reverse_iterator	rbegin() {
				return (reverse_iterator(_root.tree_max()));
			}
			
			const_reverse_iterator	rbegin() const {
				return (const_reverse_iterator(_root.tree_max()));
			}

			reverse_iterator	rend() {
				return (++reverse_iterator(begin()));
			}

			const_reverse_iterator	rend() const {
				return (++const_reverse_iterator(begin()));
			}

			bool	empty() const {
				if (_size == 0)
					return true;
				return false;
			};

			size_type	size() const {
				return _size;
			};

			size_type	max_size() const {
				return (size_type(-1) / sizeof(Node<value_type>));
			};

			mapped_key	&operator[](const key_type &key) {
				nodePtr	node;

				if ((node = _root.find(key)))
					return node->value.second;
				return (*(this->insert(ft::make_pair(key, mapped_key())).first)).second;
			};

			pair<iterator, bool>	insert(const value_type &val) {
				if (count(val.first))
					return (ft::make_pair(find(val.first), 0));
				_root.insert(val);
				_size++;
				return (ft::make_pair(find(val.first), 1));
			};

			iterator	insert(iterator position, const value_type &val) {
				position = insert(val).first;
				return position;
			};

			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last) {
				for (; first != last; first++)
					insert(ft::make_pair(first->first, first->second));
			};

			void	erase(iterator position) {
				erase(position->first);
			};

			size_type	erase(const key_type &val) {
				if (count(val))
				{
					_root.erase(val);
					_size = _size == 0 ? 0 : _size - 1;
					return 1;
				}
				return 0;
			};

			void	erase(iterator first, iterator last) {
				iterator	tmp = first;

				while (tmp != last) {
					first = tmp;
					tmp++;
					erase(first);
				}
			};

			void	swap(map &x) {
				map				tmp;
				key_compare		tmp_cmp = x.cmp;
				allocator_type	tmp_alloc = x._alloc;

				tmp = x;
				x = *this;
				*this = tmp;
				this->cmp = tmp_cmp;
				this->_alloc = tmp_alloc;
			};

			void	clear() {
				_root.clear();
				_size = 0;
			};

			key_compare	key_comp() const {
				key_compare	comp;

				return comp;
			};

			value_compare	value_comp() const {
				value_compare	comp;

				return comp;
			};

			iterator	find(const key_type &key) {
				nodePtr	node;

				if ((node = _root.find(key)))
					return iterator(node);
				return (this->end());
			}

			const_iterator	find(const key_type &key) const {
				nodePtr	node;

				if ((node = _root.find(key)))
					return const_iterator(node);
				return (this->end());
			}

			size_type	count(const key_type &key) const {
				if (_size == 0)
					return 0;
				if (_root.find(key) != nullptr)
					return 1;
				return 0;
			};

			iterator	lower_bound(const key_type &key) {
				iterator	it = this->begin();

				while (it != this->end() && cmp(it->first, key))
					it++;
				return it;
			};

			const_iterator	lower_bound(const key_type &key) const {
				const_iterator	it = this->begin();

				while (it != this->end() && cmp(it->first, key))
					it++;
				return it;
			};

			iterator	upper_bound(const key_type &key) {
				iterator	it = this->begin();

				while (it != this->end() && !cmp(key, it->first))
					it++;
				return it;
			};

			const_iterator	upper_bound(const key_type &key) const {
				const_iterator	it = this->begin();

				while (it != this->end() && !cmp(key, it->first))
					it++;
				return it;
			};

			pair<iterator, iterator>	equal_range(const key_type &key) {
				if (!cmp(key, _root.tree_max()->value.first))
					return (ft::make_pair<iterator, iterator> (this->end(), this->end()));
				return (ft::make_pair<iterator, iterator> (lower_bound(key), upper_bound(key)));
			};

			void	graphical_print(int space) {
				printHelper(_root.root, space);
				std::cout << "--------------------------------------------" << std::endl;
			};

		private:
			tree			_root;
			allocator_type	_alloc;
			size_type		_size;
			key_compare		cmp;
	};
}

#endif