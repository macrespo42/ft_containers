#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>
#include <iostream>

int main(void)
{
	ft::vector<int> ft;
	std::vector<int> original;

	ft::vector_iterator<int> a;
	ft::vector_iterator<int> b(a);
	a = b;
	if (a == b)
		std::cout << "a is equal to b" << std::endl;
	else
		std::cout << "a is not equal to b" << std::endl;

	if (a != b)
		std::cout << "a is different of b" << std::endl;
	else
		std::cout << "a is same as b" << std::endl;

	std::cout << *a << std::endl;
	return 0;
}