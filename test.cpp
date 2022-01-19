#include <vector>
#include <iostream>

template<typename T>
void	print_vector(std::vector<T> &vec, std::string const &msg)
{
	std::cout << std::endl << msg << std::endl << "\t";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout  << "[" << *it << "]";
	std::cout << std::endl;
	std::cout << "Size : " << vec.size() << "\t" << "Capacity : " << vec.capacity() << std::endl;
}

int	main()
{
	std::vector<int> vec;
	std::vector<int> vec_assign;
	std::vector<int>::iterator it;


	std::cout << "vector vec is empty : " << vec.empty() << std::endl;
	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	print_vector(vec, "My vector");
	std::cout << std::endl << "vector vec is not empty : " << vec.empty() << std::endl;
	std::cout << std::endl << "Front of vec : " << vec.front() << std::endl;
	std::cout << std::endl << "Back of vec : " << vec.back() << std::endl;
	vec.pop_back();
	print_vector(vec, "Pop back from vec : ");
	std::cout << std::endl << "Element in index = 3 using at() : " << "[" << vec.at(3) << "]"<< std::endl;
	try {
		std::cout << "Element in index = 15 using at() : " << "[" << vec.at(15) << "]"<< std::endl;
	}
	catch (std::exception &ofr)
	{
		std::cout << ofr.what() << "]" << "\n";
	}
	std::cout << std::endl;
	std::cout << "max size : " << vec.max_size() << std::endl << std::endl;
	it = vec.begin();
	vec.resize(5);
	print_vector(vec, "Resize with size smaller than the size of vec : ");
	it = vec.begin();
	vec.resize(10, 42);
	print_vector(vec, "Resize with size = 10, bigger than the size of vec : ");
	it = vec.begin();
	vec.resize(20, 1337);
	print_vector(vec, "Resize with size = 20 bigger than the capacity of vec : ");
	it = vec.begin();
	vec_assign.assign(it + 2, it + 6);
	print_vector(vec_assign, "Assigning to empty vector from vec : ");
	for (int i = 10; i < 30; i++)
		vec.push_back(i);
	print_vector(vec, "vector : ");
	it = vec.begin();
	vec_assign.assign(it + 9, it + 23);
	print_vector(vec_assign, "Assigning to filled vector with values between the 9th and 23rd indexes of vec : ");
	it = vec.begin();
	vec_assign.assign(5, 1337);
	print_vector(vec_assign, "Assigning to filled vector with a default value : ");
	it = vec_assign.begin();
	vec_assign.insert(it + 3, 42);
	print_vector(vec_assign, "Inserting [42] in the 3rd index : ");
	it = vec_assign.begin();
	vec_assign.insert(it + 4, 13, 13);
	print_vector(vec_assign, "Inserting a range = 13 of [42] starting from the 4th index : ");
	it = vec_assign.begin();
	vec_assign.insert(it + 3, vec.begin() + 5, vec.begin() + 10);
	print_vector(vec_assign, "Inserting a range = 5 starting from the 3rd index of vec, between the 5th and 10th indexes : ");
	it = vec_assign.begin();
	vec_assign.erase(it + 5);
	print_vector(vec_assign, "Erasing the 5th element : ");
	it = vec_assign.begin();
	vec_assign.erase(it + 9, it + 21);
	print_vector(vec_assign, "Erasing all elements between 5th and 21st indexes : ");
	vec.swap(vec_assign);
	print_vector(vec, "vec after swap : ");
	print_vector(vec_assign, "vec_assign after swap : ");
	vec.insert(vec.begin(), 42);
	print_vector(vec, "Added [42] to vec after swap : ");
	print_vector(vec_assign, "vec_assign : ");
	vec.insert(vec.begin() - 3, 42);
	print_vector(vec, "Added [42] to vec after swap : ");
	it = vec_assign.begin();
	vec_assign.insert(it + 3, 5);
	print_vector(vec_assign, "vec_assign : ");
	return 0;
}