#ifndef UNIT_TEST
#define UNIT_TEST

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <deque>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"


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

/********************************************
*********************************************
****************FT MAP TESTS*****************
*********************************************
********************************************/

int map_constructors_test(void);
int map_assignation_test(void);
int map_begin_end_test(void);
int map_rbegin_rend_test(void);
int map_empty_test(void);
int map_size_test(void);
int map_max_size_test(void);
int map_operator_hook_test(void);
int map_insert_test(void);
int map_erase_test(void);
int map_swap_test(void);
int map_clear_test(void);
int map_key_comp_test(void);
int map_value_comp_test(void);
int map_find_test(void);
int map_count_test(void);
int map_lower_bound_test(void);
int map_upper_bound_test(void);
int map_equal_bound_test(void);
int map_unit_test(void);

#endif