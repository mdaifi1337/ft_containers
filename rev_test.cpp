// operator- on reverse_iterator
#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include "Vector.hpp"      // std::vector

int main () {
	ft::Vector<int> myvector;

	for (int i=0; i < 10; i++)
		myvector.push_back(i);

	ft::reverse_iterator<ft::Vector<int>::iterator> from,until;

	from = myvector.rbegin(); // base.end()
	until = myvector.rend(); // base.begin()

	std::cout << "from " << *(from.base() - 1) << "\n";
	std::cout << "until " << *until.base() << "\n";
	std::cout << "myvector has " << (until-from) << " elements.\n";
	while (from != until)
	{
		std::cout << "[" << *from << "]";
		from++;
	}
	std::cout << std::endl;

	return 0;
}