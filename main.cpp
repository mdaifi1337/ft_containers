#include "Vector.hpp"
#include "Stack.hpp"
#include <vector>
#include <stack>
#include <list>
#include <map>
#include <utility>

template<typename T>
void	print_vector(NS::vector<T> &vec, std::string const &msg)
{
	std::cout << std::endl << msg << std::endl << "\t";
	for (NS::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout  << "[" << *it << "]";
	std::cout << std::endl;
	std::cout << "Size :" << vec.size() << "\t" << "Capacity :" << vec.capacity() << std::endl;
}

int	main()
{
	{
		NS::vector<int> vec;
		NS::vector<int> vec_assign;
		NS::vector<int> vec3;
		NS::vector<int>::iterator it;
		std::cout << "~~~~~~~~~~~ Testing vector container ~~~~~~~~~~~ " << std::endl << std::endl;


		std::cout << "vector vec is empty :" << vec.empty() << std::endl;
		for (int i = 0; i < 10; i++)
			vec.push_back(i);
		print_vector(vec, "My vector");
		std::cout << std::endl << "vector vec is not empty :" << vec.empty() << std::endl;
		std::cout << std::endl << "Front of vec :" << vec.front() << std::endl;
		std::cout << std::endl << "Back of vec :" << vec.back() << std::endl;
		vec.pop_back();
		print_vector(vec, "Pop back from vec :");
		std::cout << std::endl << "Element in index = 3 using at() :" << "[" << vec.at(3) << "]"<< std::endl;
		try {
			std::cout << "Element in index = 15 using at() :" << "[" << vec.at(15) << "]"<< std::endl;
		}
		catch (std::exception &ofr)
		{
			std::cout << ofr.what() << "]" << "\n";
		}
		NS::vector<int> vec2(vec.begin() + 3, vec.begin() + 7);
		print_vector(vec2, "Assigning to vec2 a range of vec :");
		std::cout << std::endl;
		vec3 = vec2;
		vec2 = NS::vector<int>();
		print_vector(vec2, "Vec2 after assignment operator :");
		std::cout << std::endl;
		print_vector(vec3, "Vec3 after assignment operator :");
		std::cout << std::endl;
		vec2 = NS::vector<int>(vec3);
		print_vector(vec2, "Vec2 after copy construction :");
		std::cout << std::endl;
		vec3[2] = 1337;
		print_vector(vec2, "Vec2 after modifying vec3[2] element :");
		std::cout << std::endl;
		print_vector(vec3, "Vec3 after modifying its 3rd element :");
		std::cout << std::endl;
		std::cout << "max size :" << vec.max_size() << std::endl << std::endl;
		it = vec.begin();
		vec.resize(5);
		print_vector(vec, "Resize with size smaller than the size of vec :");
		it = vec.begin();
		vec.resize(10, 42);
		print_vector(vec, "Resize with size = 10, bigger than the size of vec :");
		it = vec.begin();
		vec.resize(20, 1337);
		print_vector(vec, "Resize with size = 20 bigger than the capacity of vec :");
		it = vec.begin();
		vec_assign.assign(it + 2, it + 6);
		print_vector(vec_assign, "Assigning to empty vector from vec :");
		for (int i = 10; i < 30; i++)
			vec.push_back(i);
		print_vector(vec, "vector :");
		it = vec.begin();
		vec_assign.assign(it + 9, it + 23);
		print_vector(vec_assign, "Assigning to filled vector with values between the 9th and 23rd indexes of vec :");
		it = vec.begin();
		vec_assign.assign(5, 1337);
		print_vector(vec_assign, "Assigning to filled vector with a default value :");
		it = vec_assign.begin();
		vec_assign.insert(it + 3, 42);
		print_vector(vec_assign, "Inserting [42] in the 3rd index :");
		it = vec_assign.begin();
		vec_assign.insert(it + 4, 13, 13);
		print_vector(vec_assign, "Inserting a range = 13 of [42] starting from the 4th index :");
		it = vec_assign.begin();
		vec_assign.insert(it + 3, vec.begin() + 5, vec.begin() + 10);
		print_vector(vec_assign, "Inserting a range = 5 starting from the 3rd index of vec, between the 5th and 10th indexes :");
		it = vec_assign.begin();
		vec_assign.erase(it + 5);
		print_vector(vec_assign, "Erasing the 5th element :");
		it = vec_assign.begin();
		vec_assign.erase(it + 9, it + 21);
		print_vector(vec_assign, "Erasing all elements between 9th and 21st indexes :");
		vec.swap(vec_assign);
		print_vector(vec, "vec after swap :");
		print_vector(vec_assign, "vec_assign after swap :");
		vec.insert(vec.begin(), 42);
		print_vector(vec, "Added [42] to vec after swap :");
		it = vec_assign.begin();
		vec_assign.insert(it + 3, 5);
		print_vector(vec_assign, "Inserting 5 in the 3rd index of vec_assign :");
		vec.clear();
		print_vector(vec, "vec was cleared :");
		int *p;
		p = vec.get_allocator().allocate(5);
		for (int i = 0; i < 5; i++)
			vec.get_allocator().construct(&p[i], i);
		std::cout << std::endl << "Allocating p with 5 elements using vec's allocator :" << std::endl << "\t";
		for (int i = 0; i < 5; i++)
			std::cout  << "[" << p[i] << "]";
		std::cout << std::endl << std::endl;
		std::cout << "Testing if two vectors are equal :" << std::endl;
		vec = NS::vector<int>(p, p+5);
		vec2 = NS::vector<int>(p, p+5);
		if (vec == vec2)
			std::cout << "\t" << "vec and vec2 are equal (equal function)" << std::endl;
		if (vec <= vec2)
			std::cout << "\t" << "vec is less than or equal to vec2 (lexicographical_compare function)" << std::endl;
		if (vec >= vec2)
			std::cout << "\t" << "vec is greater than or equal to vec2(lexicographical_compare function)" << std::endl;
		if (vec != vec3)
			std::cout << "\t" << "vec and vec3 are not equal (equal function)" << std::endl;
		std::cout << std::endl;
		std::cout << "Testing if two vectors are not equal :" << std::endl;
		vec2[3] = 1337;
		if (vec != vec2)
			std::cout << "\t" << "vec and vec2 are not equal (equal function)" << std::endl;
		if (vec < vec2) 
			std::cout << "\t" << "vec is less than vec2 (lexicographical_compare function)" << std::endl;
		if (vec > vec2)
			std::cout << "\t" << "vec is greater than vec2 (lexicographical_compare function)" << std::endl;
		std::cout << std::endl;
	}

	{
		NS::stack<int>	st;
		NS::stack<int>	st3;
		NS::stack<int, std::list<int> >	st2;
		int				sum = 0;
		std::cout << "~~~~~~~~~~~ Testing stack container ~~~~~~~~~~~ " << std::endl << std::endl;

		std::cout << std::endl << "Testing stack with default underlying container (ft::vector) :" << std::endl;
		for (int i = 1; i <= 10; i++)
			st.push(i);

		while (!st.empty())
		{
			std::cout << "[" << st.top() << "] ";
			sum += st.top();
			st.pop();
		}
		std::cout << std::endl << "sum = " << sum << std::endl;

		std::cout << std::endl << "Testing stack with std::list as underlying container :" << std::endl;
		for (int i = 1; i <= 10; i++)
			st2.push(i);

		while (!st2.empty())
		{
			std::cout << "[" << st2.top() << "] ";
			sum += st2.top();
			st2.pop();
		}
		std::cout << std::endl << "sum = " << sum << std::endl;

		for (int i = 1; i <= 10; i++)
		{
			st.push(i);
			st3.push(i);
		}
		std::cout << std::endl;
		std::cout << "Testing equality of two stacks :" << std::endl;
		if (st == st3)
			std::cout << "st and st3 are equal" << std::endl;
		if (st >= st3)
			std::cout << "st is greater than or equal to st3" << std::endl;
		if (st <= st3)
			std::cout << "st is less than or equal to st3" << std::endl;
		std::cout << std::endl << "Called pop() on st :" << std::endl;
		st.pop();
		if (st != st3)
			std::cout << "st and st3 are not equal" << std::endl;
		if (st > st3)
			std::cout << "st is greater than st3" << std::endl;
		if (st < st3)
			std::cout << "st is less than st3" << std::endl;
	}
	return 0;
}
