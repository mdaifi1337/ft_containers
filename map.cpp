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

	ft::map<int, int> mp;
	BST	bst;

	mp.insert(ft::pair<int, int>(10, 10));
	mp.insert(ft::pair<int, int>(20, 20));
	mp.insert(ft::pair<int, int>(30, 30));
	mp.insert(ft::pair<int, int>(25, 25));
	mp.insert(ft::pair<int, int>(5, 5));
	mp.insert(ft::pair<int, int>(15, 15));
	mp.insert(ft::pair<int, int>(40, 40));
	mp.insert(ft::pair<int, int>(60, 60));
	mp.insert(ft::pair<int, int>(4, 4));
	mp.insert(ft::pair<int, int>(35, 35));
	mp.insert(ft::pair<int, int>(27, 27));
	mp.insert(ft::pair<int, int>(8, 8));
	mp.insert(ft::pair<int, int>(19, 19));
	mp.insert(ft::pair<int, int>(26, 26));
	mp.insert(ft::pair<int, int>(13, 13));
	mp.print_tree(0);
	std::cout << "--------------------------------------------" << std::endl;
	mp.erase(20);
	mp.print_tree(0);
	// std::cout << "--------------------------------------------" << std::endl;
	// mp.print_tree(0);
	return 0;
}