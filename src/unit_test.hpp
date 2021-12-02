#ifndef UNIT_TEST
#define UNIT_TEST

#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include "vector.hpp"
#include "stack.hpp"


#ifdef FT
	using namespace ft;
#else
	using namespace std;
#endif

/********************************************
*********************************************
***************FT VECTOR TESTS***************
*********************************************
********************************************/

void vec_vectorConstructor_test(void);
void vec_vectorAssignation_test(void);
void vec_beginEnd_test(void);
void vec_rendRbegin_test(void);
void vec_size_test(void);
void vec_max_size_test(void);
void vec_resize_test(void);
void vec_capacity_test(void);
void vec_reserve_test(void);
void vec_empty_test(void);
void vec_at_test(void);
void vec_front_test(void);
void vec_back_test(void);
void vec_assign_test(void);
void vec_push_back_test(void);
void vec_pop_back_test(void);
void vec_erase_test(void);
void vec_swap_test(void);
void vec_clear_test(void);
void vec_comparaison_test(void);
int vec_vector_unit_tests(void);

/********************************************
*********************************************
***************FT STACK TESTS****************
*********************************************
********************************************/

void stack_stackConstructor_test(void);
void stack_empty_test(void);
void stack_size_test(void);
void stack_top_test(void);
void stack_push_test(void);
void stack_pop_test(void);
int stack_unit_test(void);

#endif