#ifndef TREE_HPP
#define TREE_HPP
#include <iostream>

struct Node
{
	Node *parent;
	Node *left;
	Node *right;
	int	value;
};

typedef Node*	NodePtr;

class BST
{
	private:
		NodePtr	root;
	
	public:
		BST ()
		{
			this->root = nullptr;
		};

		~BST () {};

		void	insertNode(int value)
		{
			NodePtr	node = new Node;
			NodePtr	parent = nullptr;
			NodePtr	it;

			node->value = value;
			node->left = nullptr;
			node->right = nullptr;
			node->parent = nullptr;
			it = this->root;
			while (it != nullptr)
			{
				parent = it;
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
		};

		void printHelper(NodePtr root, int space) {
			// print the tree structure on the screen
			if (root != nullptr) {
				// std::cout <<
				space += 5;
				printHelper(root->right, space);
				std::cout << std::endl;
				for (int i = 5; i < space; i++)
					std::cout << " ";
				std::cout << root->value << std::endl;

				printHelper(root->left, space);
			}
		};

		void	printTree()
		{
			std::string indent = "";
			printHelper(this->root, 0);
		};
};

#endif