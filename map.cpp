#include "pair.hpp"
#include "tree.hpp"
#include "map.hpp"
#include <iostream>
// #include <utility>
#include <map>

void	print_map(ft::map<int, int> &mp)
{
	ft::map<int, int>::iterator	it = mp.begin();
	while (it != mp.end())
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
	std::cout << "--------------------------------------------" << std::endl;
}
int main () {
	ft::map<int, int> mp;
	std::map<int, int>::iterator i;
	ft::map<int, int> mp3;
	ft::map<int, int>::iterator it, it2;
	std::cout << std::endl << "maximum size that can be allocated (but not guaranteed) is " << mp.max_size() << std::endl;
	std::cout << std::endl << "Testing if map 'mp' is empty :" << std::endl;
	if (mp.empty())
		std::cout << "map 'mp' is empty :" << std::endl;
	mp.insert(ft::pair<int, int>(10, 10));
	mp.insert(ft::pair<int, int>(20, 20));
	mp.insert(ft::pair<int, int>(30, 30));
	mp.insert(ft::pair<int, int>(25, 25));
	mp.insert(ft::pair<int, int>(5, 5));
	mp.insert(ft::pair<int, int>(15, 15));
	mp.insert(ft::pair<int, int>(40, 40));
	mp.insert(ft::pair<int, int>(27, 27));
	mp.insert(ft::pair<int, int>(25, 25));
	std::cout << std::endl << "Printing map mp :" << std::endl;
	print_map(mp);
	std::cout << std::endl << "Size of 'mp' is " << mp.size() << std::endl;
	ft::map<int, int> mp2(mp);
	std::cout << std::endl << "Printing 'mp2' after copy constructing :" << std::endl;
	print_map(mp2);
	mp.erase(20);
	std::cout << std::endl << "map 'mp' after deleting node with key 20 :" << std::endl;
	print_map(mp);
	std::cout << std::endl << "map 'mp2' after deleting node with key 20 in 'mp' :" << std::endl;
	print_map(mp2);
	mp3 = mp;
	std::cout << std::endl << "map 'mp3' after assignment constructing :" << std::endl;
	print_map(mp3);
	std::cout << std::endl << "Testing if map 'mp3' is empty :" << std::endl;
	if (mp3.empty())
		std::cout << "map 'mp3' is empty :" << std::endl;
	else
		std::cout << "map 'mp3' is not empty, its size is " << mp3.size()  << std::endl;
	std::cout << std::endl << "Testing operator[] with a key that already exists :" << std::endl;
	mp[27] = 1337;
	print_map(mp);
	std::cout << std::endl << "Testing operator[] with a new key :" << std::endl;
	mp[28] = 42;
	print_map(mp);
	mp2.clear();
	std::cout << std::endl << "Size of map 'mp2' after being cleared : " << mp2.size() << std::endl;
	it = mp.find(27);
	mp.insert(it, ft::pair<int, int>(13, 13));
	std::cout << std::endl << "Inserting 13 in 'mp' after searching for a node having 27 as a key :" << std::endl;
	print_map(mp);
	ft::map<int, int>	tmp;
	tmp.insert(ft::pair<int, int>(100, 100));
	tmp.insert(ft::pair<int, int>(200, 200));
	tmp.insert(ft::pair<int, int>(300, 300));
	tmp.insert(ft::pair<int, int>(250, 250));
	tmp.insert(ft::pair<int, int>(50, 50));
	std::cout << std::endl << "Printing map 'mp' :" << std::endl;
	print_map(mp);
	std::cout << std::endl << "Inserting a range of nodes in 'mp' from 'tmp' :" << std::endl;
	mp.insert(tmp.begin(), tmp.end());
	print_map(mp);
	std::cout << std::endl << "Erasing the node with key 40 from 'mp' :" << std::endl;
	it = mp.find(40);
	mp.erase(it);
	print_map(mp);
	std::cout << std::endl << "Erasing a range of nodes from map 'mp' :" << std::endl;
	it = mp.find(10);
	it2 = mp.find(300);
	mp.erase(it, it2);
	print_map(mp);
	std::cout << std::endl << "Swapping 'mp' and 'tmp' :" << std::endl;
	tmp.swap(mp);
	std::cout << "'mp' after swap :" << std::endl;
	print_map(mp);
	std::cout << "'tmp' after swap :" << std::endl;
	print_map(tmp);
	std::cout << std::endl << "inserting 350 to 'tmp' after swap :" << std::endl;
	tmp.insert(ft::pair<int, int>(350, 350));
	std::cout << "'tmp' :" << std::endl;
	print_map(tmp);
	std::cout << "'mp' :" << std::endl;
	print_map(mp);
	std::cout << std::endl << "Testing iterator on map 'mp' :" << std::endl;
	// std::cout << std::endl << "mp end :" << mp.end()->second << std::endl;
	it = mp.begin();
	while (it != mp.end())
	{
		std::cout << it->first << " => " << it->second << std::endl;
		it++;
	}
	std::cout << std::endl << "Testing reverse iterator on map 'mp' :" << std::endl;
	ft::map<int, int>::reverse_iterator	rev_begin, rev_end;
	rev_begin = mp.rbegin();
	rev_end = mp.rend();
	for (; rev_begin != rev_end; rev_begin++)
		std::cout << rev_begin->first << " => " << rev_begin->second << std::endl;
	std::cout << std::endl << "Testing lower_bound() on map 'mp' :" << std::endl;
	std::cout << "Lower bound of 70 is [" << mp.lower_bound(70)->first << "] => " << mp.lower_bound(70)->second << std::endl;
	std::cout << "Lower bound of 100 is [" << mp.lower_bound(100)->first << "] => " << mp.lower_bound(100)->second << std::endl;
	std::cout << std::endl << "Testing upper_bound() on map 'mp' :" << std::endl;
	std::cout << "upper bound of 240 is [" << mp.upper_bound(240)->first << "] => " << mp.upper_bound(240)->second << std::endl;
	std::cout << "upper bound of 250 is [" << mp.upper_bound(250)->first << "] => " << mp.upper_bound(250)->second << std::endl;
	std::cout << std::endl << "Testing key_comp() on map 'mp' :" << std::endl;
	ft::map<int,int>::key_compare mycomp = mp.key_comp();
	int highest = mp.rbegin()->first;  // key value of last element
	it = mp.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest));
	std::cout << std::endl << "Testing value_comp() on map 'mp' :" << std::endl;
	ft::pair<int,int> p = *mp.rbegin();          // last element
	it = mp.begin();
	do {
		std::cout << it->first << " => " << it->second << '\n';
	} while ( mp.value_comp()(*it++, p) );

	std::cout << std::endl << "Testing equal_range() on map 'mp' :" << std::endl;
	ft::pair<ft::map<int,int>::iterator,ft::map<int,int>::iterator> ret;
	ret = mp.equal_range(100);
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';
	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';
	// while (1)
	// 	;
	return 0;
}