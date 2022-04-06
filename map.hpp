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

			tree	copy_tree(NodePtr root)
			{
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

			tree	&operator=(const tree &other)
			{
				copy_tree(other.root);
				return *this;
			};

			tree() {
				this->root = nullptr;
			};
			~tree() {
				delete root;
			};

			int	height(NodePtr node)
			{
				if (node == nullptr)
					return 0;
				return node->height;
			}

			int	max(int val1, int val2)
			{
				return val1 < val2 ? val2 : val1;
			}

			NodePtr	newNode(value_type val)
			{
				NodePtr	node = new Node<value_type>(val);
				// node->value = val;
				node->left = nullptr;
				node->right = nullptr;
				node->parent = nullptr;
				node->height = 1;
				return node;
			}

			void	insert(value_type value)
			{
				this->root = insert_node(this->root, value, this->root);
			};

			NodePtr	insert_node(NodePtr _root, value_type value, NodePtr parent)
			{
				NodePtr	node;

				// it = this->root;
				// while (it != nullptr)
				// {
				// 	parent = it;
				// 	if (node->value < it->value)
				// 		it = it->left;
				// 	else if (node->value > it->value)
				// 		it = it->right;
				// 	else
				// 		return it;
				// }
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

				// 	std::cout << "Printing tree before balancing : " << std::endl;
				// printHelper(root, 0);
				// 	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
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

			NodePtr	deleteNode(NodePtr node, key_type key)
			{
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
						// node->value.second = tmp->value.second; // Not sure it should be value or value.second (aka should the key change or not)
						// node->right = deleteNode(node->right, tmp->value.first);
						delete node;
					}
				}
				if (tmp == nullptr)
					return tmp;
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

			void	erase(key_type key)
			{
				this->root = this->deleteNode(this->root, key);
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

			NodePtr	left_rotate(NodePtr node)
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

				node->height = max(height(node->left), height(node->right)) + 1;
				tmp->height = max(height(tmp->left), height(tmp->right)) + 1;
				return (tmp);
			}

			NodePtr	right_rotate(NodePtr node)
			{
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

			int	getBalance(NodePtr node)
			{
				if (node == nullptr)
					return 0;
				return height(node->left) - height(node->right);
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
					my_val_comp(){};
					~my_val_comp(){};
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

			typedef T												mapped_key;
			typedef ft::pair<const key_type, mapped_key>			value_type;
			typedef my_val_comp<value_type, key_type>				value_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			// typedef ft::map_iterator<pointer>						iterator;
			// typedef ft::map_iterator<const_pointer>					const_iterator;
			// typedef ft::map_reverse_iterator<pointer>				reverse_iterator;
			// typedef ft::mapreverse__iterator<const_pointer>			const_reverse_iterator;
			typedef ptrdiff_t										difference_type;
			typedef size_t											size_type;
			typedef tree<value_type, key_type, allocator_type, key_compare>	tree;


		public:
			// struct BST	tree;
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _size(0)
			{};

			void	insert(const value_type &val)
			{
				_root.insert(val);
			};

			void	erase(const key_type &val)
			{
				_root.erase(val);
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