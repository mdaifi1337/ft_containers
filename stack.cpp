#include "Stack.hpp"
#include <stack>
#include <list>

int main()
{
	ft::stack<int>	st;
	ft::stack<int, std::list<int> >	st2;
	int				sum = 0;

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
		st2.push(i);
	std::cout << std::endl;

	return 0;
}