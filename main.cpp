#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>

int main(void)
{
	ft::vector<int> ft;
	std::vector<int> original;

	ft::vector_iterator<int> a;
	ft::vector_iterator<int> b(a);
	a = b;
	return 0;
}