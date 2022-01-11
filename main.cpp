#include "Vector.hpp"

int	main()
{
	ft::Vector<int> vec;
	ft::Vector<int> vec_assign;
	ft::Vector<int>::iterator it;

	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	std::cout << "My vector : " << std::endl << "\t";
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout  << "[" << *it << "]";
	it = vec.begin();
	std::cout << std::endl << std::endl;
	std::cout << "Element in the 3rd position : " << "[" << it[3] << "]" << std::endl;
	std::cout << "Size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	// std::cout << std::endl;
	// std::cout << "My vector backwards : " << std::endl << "\t";
	// for (it = vec.end() - 1; it != vec.begin(); it--)
	// 	std::cout << "[" << *it << "]";
	std::cout << std::endl;
	std::cout << "max size : " << vec.max_size() << std::endl << std::endl;
	std::cout << "Resize with smaller size : " << std::endl;
	vec.resize(5);
	std::cout << "\t" << "My vector : " << std::endl << "\t" << "\t";
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout  << "[" << *it << "]";
	std::cout << std::endl << std::endl;
	std::cout << "Size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	std::cout << std::endl;
	std::cout << "Assigned empty vector : " << std::endl << "\t";
	it = vec.begin();
	vec_assign.assign(it + 2, it + 6);
	for (ft::Vector<int>::iterator it2 = vec_assign.begin(); it2 != vec_assign.end(); it2++)
		std::cout  << "[" << *it2 << "]";
	std::cout << std::endl << std::endl;
	std::cout << "Size : " << vec_assign.size() << "\t" << "Capacity : " << vec_assign.capacity() << std::endl;
	std::cout << std::endl;
	std::cout << "Assigned filled vector : " << std::endl << "\t";
	for (int i = 10; i < 30; i++)
		vec.push_back(i);
	it = vec.begin();
	vec_assign.assign(it + 9, it + 23);
	for (ft::Vector<int>::iterator it2 = vec_assign.begin(); it2 != vec_assign.end(); it2++)
		std::cout  << "[" << *it2 << "]";
	std::cout << std::endl << std::endl;
	std::cout << "Size : " << vec_assign.size() << "\t" << "Capacity : " << vec_assign.capacity() << std::endl;
	it = vec.begin();
	vec_assign.assign(5, 1337);
	for (ft::Vector<int>::iterator it2 = vec_assign.begin(); it2 != vec_assign.end(); it2++)
		std::cout  << "[" << *it2 << "]";
	std::cout << std::endl << std::endl;
	std::cout << "Size : " << vec_assign.size() << "\t" << "Capacity : " << vec_assign.capacity() << std::endl;
	return 0;
}
