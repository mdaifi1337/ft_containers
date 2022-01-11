
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vec;
	std::vector<int> vec2;
	std::vector<int>::iterator it;

	std::cout << "size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
		// vec.push_back(2);
	for (std::vector<int>::iterator it2 = vec.begin(); it2 != vec.end(); it2++)
		std::cout << "[" << *it2 << "]";
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	std::cout << std::endl;
	vec.resize(5);
	for (std::vector<int>::iterator it2 = vec.begin(); it2 != vec.end(); it2++)
		std::cout << "[" << *it2 << "]";
	std::cout << std::endl;
	std::cout << "size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	it = vec.begin();
	vec2.assign(it + 2, it + 6);
	std::cout << std::endl;
	for (std::vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); it2++)
		std::cout << "[" << *it2 << "]";
	std::cout << std::endl;
	std::cout << "size : " << vec2.size() << "\t" << "Capacity : " << vec2.capacity() << std::endl;
	for (int i = 10; i < 30; i++)
		vec.push_back(i);
	it = vec.begin();
	vec2.assign(it + 9, it + 23);
	std::cout << std::endl;
	for (std::vector<int>::iterator it2 = vec2.begin(); it2 != vec2.end(); it2++)
		std::cout << "[" << *it2 << "]";
	std::cout << std::endl;
	std::cout << "size : " << vec2.size() << "\t" << "Capacity : " << vec2.capacity() << std::endl;
	// vec.resize(5);
	// for (size_t i = 0; i < 10; i++)
	// 	std::cout << "[" << vec[i] << "]";
	// std::cout << std::endl;
	// std::cout << "size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
	// std::cout << std::endl;
	// vec.resize(5);
	return (0);
}