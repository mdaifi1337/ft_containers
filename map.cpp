#include "pair.hpp"
#include "tree.hpp"
#include "map.hpp"
#include <iostream>
#include <utility>

int main () {
//   ft::pair <std::string,double> product1;                     // default constructor
//   ft::pair <std::string,double> product2 ("tomatoes",2.30);   // value init
//   ft::pair <std::string,double> product3 (product2);          // copy constructor

//   product1 = ft::make_pair(std::string("lightbulbs"),0.99);   // using make_pair (move)

//   product2.first = "shoes";                  // the type of first is string
//   product2.second = 39.90;                   // the type of second is double

//   std::cout << "The price of " << product1.first << " is $" << product1.second << '\n';
//   std::cout << "The price of " << product2.first << " is $" << product2.second << '\n';
//   std::cout << "The price of " << product3.first << " is $" << product3.second << '\n';

	ft::map<std::string, int> mp;
	BST	bst;

	mp.insert(ft::pair<std::string, int>("one", 1));
	// bst.insertNode(15);
	// bst.insertNode(8);
	// bst.insertNode(23);
	// bst.insertNode(18);
	// bst.insertNode(4);
	// bst.insertNode(6);
	// bst.insertNode(3);
	// bst.insertNode(14);
	// bst.insertNode(25);
	mp.printHelper(mp._root.root, 0);
	return 0;
}