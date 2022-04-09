#include "pair.hpp"
#include "tree.hpp"
#include "map.hpp"
#include <iostream>
#include <utility>
#include <map>


int main () {
	ft::map<int, int> mp;
	ft::map<int, int>::iterator it;

	mp.insert(ft::pair<int, int>(10, 10));
	mp.insert(ft::pair<int, int>(20, 20));
	mp.insert(ft::pair<int, int>(30, 30));
	mp.insert(ft::pair<int, int>(25, 25));
	mp.insert(ft::pair<int, int>(5, 5));
	mp.insert(ft::pair<int, int>(15, 15));
	mp.insert(ft::pair<int, int>(40, 40));
	mp.insert(ft::pair<int, int>(27, 27));
	std::cout << "Printing map mp :" << std::endl;
	mp.print_tree(0);
	// for (it = mp.begin(); it != mp.end(); it++)
	// 	std::cout << it->first << " => " << it->second << std::endl;
	ft::map<int, int> mp2(mp);
	mp.erase(20);
	mp.print_tree(0);
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Printing mp2 after copy constructing :" << std::endl;
	mp2.print_tree(0);
	// std::cout << "--------------------------------------------" << std::endl;
	return 0;
}