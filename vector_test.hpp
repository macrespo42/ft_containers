#ifndef VECTOR_TEST
#define VECTOR_TEST

#include "vector.hpp"
#include "vector_iterator.hpp"
#include <vector>
#include <iostream>
#include <vector>

namespace vec
{
	void vectorConstructor_test(void);
	void vectorAssignation_test(void);
	void beginEnd_test(void);
	void rendRbegin_test(void);
	void size_test(void);
	void max_size_test(void);
	void resize_test(void);
	void capacity_test(void);
	void reserve_test(void);
	void empty_test(void);
	void at_test(void);
	void front_test(void);
	void back_test(void);
	void assign_test(void);
	void push_back_test(void);
	void pop_back_test(void);
	void erase_test(void);
	void swap_test(void);
	void clear_test(void);
	void comparaison_test(void);
	int vector_unit_tests(void);
}

#endif