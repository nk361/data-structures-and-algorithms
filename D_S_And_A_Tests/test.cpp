#include "pch.h"
#include <array>
#include <vector>

#include "../D_S_and_A/Algorithms/c_general_algorithms.h"

#include "../D_S_and_A/Data Structures Headers/c_poly_node.h"
#include "../D_S_and_A/Data Structures Headers/c_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_binary_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_avl_binary_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_heap.h"
#include "../D_S_and_A/Data Structures Headers/c_max_heap.h"
#include "../D_S_and_A/Data Structures Headers/c_min_heap.h"
#include "../D_S_and_A/Data Structures Headers/c_linked_list.h"
#include "../D_S_and_A/Data Structures Headers/c_red_black_poly_node.h"
#include "../D_S_and_A/Data Structures Headers/c_red_black_binary_tree.h"

#include "../D_S_and_A/Data Structures Headers/Iterators/c_linked_list_iterator.h"
#include "../D_S_and_A/Data Structures Headers/Iterators/c_bst_iterator_in_order.h"

#include "../D_S_and_A/Algorithms/c_bubble_sort.h"
#include "../D_S_and_A/Algorithms/c_comb_sort.h"
#include "../D_S_and_A/Algorithms/c_counting_sort.h"
#include "../D_S_and_A/Algorithms/c_max_heap_sort.h"
#include "../D_S_and_A/Algorithms/c_min_heap_sort.h"
#include "../D_S_and_A/Algorithms/c_bst_sorts.h"
#include "../D_S_and_A/Algorithms/c_merge_sort.h"
#include "../D_S_and_A/Algorithms/c_quick_sort.h"
#include "../D_S_and_A/Algorithms/c_heap_sort.h"

#include "../D_S_and_A/Algorithms/c_deep_learning.h"

TEST(c_general_algorithms_header, c_small_general_algorithms)
{
	std::vector<int> sorted_vector{ 1, 2, 3, 4, 5 };
	c_general_algorithms::scramble_vals(sorted_vector);
	EXPECT_FALSE(sorted_vector[0] == 1 && sorted_vector[1] == 2 && sorted_vector[2] == 3 && sorted_vector[3] == 4 && sorted_vector[4] == 5);

	std::vector<std::string> sorted_strings{ "Amy", "Briana", "Cathy", "Darcy", "Emily", "Fatima", "Gracie", "Hannah" };
	c_general_algorithms::scramble_vals(sorted_strings);
	EXPECT_FALSE(sorted_strings[0] == "Amy" && sorted_strings[1] == "Briana" && sorted_strings[2] == "Cathy" && sorted_strings[3] == "Darcy" && sorted_strings[4] == "Emily" && sorted_strings[5] == "Fatima" && sorted_strings[6] == "Gretchen" && sorted_strings[7] == "Hannah");

	std::vector<int> const values_to_sum{ 5, 2, 9, 8, 4, 10, 15 };
	std::pair<int, int> twelve{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 12) };
	EXPECT_EQ(twelve.first, 8);
	EXPECT_EQ(twelve.second, 4);
	std::pair<int, int> nineteen{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 19) };
	EXPECT_EQ(nineteen.first, 9);
	EXPECT_EQ(nineteen.second, 10);
	std::pair<int, int> twenty{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 20) };
	EXPECT_EQ(twenty.first, 5);
	EXPECT_EQ(twenty.second, 15);
	std::pair<int, int> const fifty{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 50) };
	EXPECT_TRUE(!fifty.first && !fifty.second);//Sum values not found

	//neither lambda function uses the index here, but still need to accept it to be called
	int(*multiply_sum)(int const&, int const&, int const&) { [](int const& index, int const& a, int const& b) { return a * b; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(1, 5, multiply_sum, 10, 2), 100);

	double(*add_three)(int const&, double const&, double const&, double const&) { [](int const& index, double const& a, double const& b, double const& c) { return a + b + c; } };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(1, 9, add_three, 5.5, 8.2, 10.7), 219.6);

	//lambda using the index
	double(*index_formula)(int const&, int const&) { [](int const& index, int const& x) { return pow(x, index + 2); } };//x^(n + 2)
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(-3, 5, index_formula, 4), 21845.25);

	int(*sum_arrays)(int const&, std::vector<int> const&, std::vector<int> const&) { [](int const& index, std::vector<int> const& a, std::vector<int> const& b) { return a[index] * b[index]; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(0, 2, sum_arrays, std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 4, 5, 6 }), 32);

	double(*multiply_this)(int const&, double const&, double const&, double const&) { [](int const& index, double const& a, double const& b, double const& c) { return a * index + b * index + c * index; } };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_pi(1, 3, multiply_this, 5.0, 2.0, 3.0), 6000.0);

	double(*multiple_types)(int const&, int const&, double const&) { [](int const& index, int const& x, double const& y) { return y * x; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(1, 10, multiple_types, 5, 8.2), 8.2 * 5 * 10);

	//int(*val_to_sum)(int const&) { [](int const& index) { return index * 10; } };
	//int(*sum_to_sum)(int const&, int const&, int const&, int(*)(int const&)) { [](int const& index, int const& strt, int const& nd, int(*v_t_s)(int const&)) { return c_general_algorithms::capital_sigma(strt, nd, v_t_s); } };
	//EXPECT_EQ(c_general_algorithms::capital_sigma(1, 10, sum_to_sum, 1, 10, val_to_sum), 5400);
}

TEST(c_node_header_tests, c_tree_node_constructors)
{
	c_poly_node<int> number{ 5, 2 };
	EXPECT_EQ(number.value, 5);
	EXPECT_EQ(number.children[0], nullptr);
	EXPECT_EQ(number.children[1], nullptr);

	c_poly_node<std::string> word{ "Test", 2 };
	EXPECT_STREQ(word.value.c_str(), "Test");
	EXPECT_EQ(word.children[0], nullptr);
	EXPECT_EQ(word.children[1], nullptr);

	c_poly_node<char> letter{ 'c', 5 };
	EXPECT_EQ(letter.value, 'c');
	EXPECT_EQ(letter.children[0], nullptr);
	EXPECT_EQ(letter.children[1], nullptr);
	EXPECT_EQ(letter.children[2], nullptr);
	EXPECT_EQ(letter.children[3], nullptr);
	EXPECT_EQ(letter.children[4], nullptr);

	c_poly_node<double> decimal{ 0.4, 7 };
	EXPECT_DOUBLE_EQ(decimal.value, 0.4);
	EXPECT_EQ(decimal.children[0], nullptr);
	EXPECT_EQ(decimal.children[1], nullptr);
	EXPECT_EQ(decimal.children[2], nullptr);
	EXPECT_EQ(decimal.children[3], nullptr);
	EXPECT_EQ(decimal.children[4], nullptr);
	EXPECT_EQ(decimal.children[5], nullptr);
	EXPECT_EQ(decimal.children[6], nullptr);

	c_red_black_poly_node<int> red_black{ 5, 2, false };
	EXPECT_EQ(red_black.value, 5);
	EXPECT_EQ(red_black.children[0], nullptr);
	EXPECT_EQ(red_black.children[1], nullptr);
	EXPECT_FALSE(red_black.red);
	red_black.red = true;
	EXPECT_TRUE(red_black.red);
}

TEST(c_bsts_iterators, c_bst_iterator_constructor_and_iterator_tests)
{
	c_binary_tree<int, c_poly_node<int>> only_root{ 10 };
	c_bst_iterator_in_order<int> only_root_then_end{ &only_root.root };
	EXPECT_EQ((**only_root_then_end)->value, 10);
	++only_root_then_end;
	EXPECT_EQ(**only_root_then_end, nullptr);

	c_binary_tree<int> lots_to_navigate{ { 10, 5, 15, 2, 7, 12, 18, 1, 6, 13, 20, 0, 25 } };

	/*
	 * I think this is sufficient for testing traversals
	 *
	 *	    10
	 *	    /\
	 *	   5  15
	 *	  /\  / \
	 *	  2 7 12 18
	 *	 / /  \   \
	 *	 1 6  13  20  //one dangling child each way
	 *	/          \
	 *	0           25  //two dangling nodes each way
	 *
	 */

	c_bst_iterator_in_order<int> in_order_moves{ &lots_to_navigate.root };
	EXPECT_EQ((**in_order_moves)->value, 0);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 1);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 2);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 5);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 6);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 7);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 10);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 12);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 13);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 15);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 18);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 20);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves)->value, 25);
	++in_order_moves;
	EXPECT_EQ((**in_order_moves), nullptr);

	std::vector<int> values_to_check{ 0, 1, 2, 5, 6, 7, 10, 12, 13, 15, 18, 20, 25 };
	int val_index{ 0 };
	for (c_poly_node<int>** current : lots_to_navigate)//checking for for each compatibility, it uses begin(), end(), !=, *, and prefix of ++
	{
		EXPECT_EQ((*current)->value, values_to_check[val_index]);
		++val_index;
	}

	c_binary_tree<int> all_left{ { 10, 9, 8, 7, 6, 5, 4, 3, 2 } };
	c_bst_iterator_in_order<int> in_order_moves_all_left{ &all_left.root };
	EXPECT_EQ((**in_order_moves_all_left)->value, 2);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 3);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 4);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 5);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 6);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 7);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 8);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 9);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left)->value, 10);
	++in_order_moves_all_left;
	EXPECT_EQ((**in_order_moves_all_left), nullptr);

	c_binary_tree<int> all_right{ { 10, 11, 12, 13, 14, 15, 16, 17, 18 } };
	c_bst_iterator_in_order<int> in_order_moves_all_right{ &all_right.root };
	EXPECT_EQ((**in_order_moves_all_right)->value, 10);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 11);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 12);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 13);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 14);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 15);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 16);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 17);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right)->value, 18);
	++in_order_moves_all_right;
	EXPECT_EQ((**in_order_moves_all_right), nullptr);

	c_binary_tree<int> one_left_test_rightmost_check{ { 10, 5, 6, 7, 8, 9, 11 } };
	c_bst_iterator_in_order<int> in_order_moves_rightmost_check{ &one_left_test_rightmost_check.root };
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 5);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 6);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 7);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 8);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 9);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 10);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check)->value, 11);
	++in_order_moves_rightmost_check;
	EXPECT_EQ((**in_order_moves_rightmost_check), nullptr);
}

TEST(c_binary_tree_tests, c_binary_tree_function_tests)
{
	c_binary_tree<int> b_tree{ 30 };
	b_tree.add_items({ 12, 72, 109, 23, 83, 22, 43, 28, 67, 43, 30 });

	EXPECT_EQ(b_tree.root->value, 30);
	EXPECT_EQ(b_tree.root->children[0]->value, 12);
	EXPECT_EQ(b_tree.root->children[1]->value, 72);
	EXPECT_EQ(b_tree.root->children[1]->children[1]->value, 109);
	EXPECT_EQ(b_tree.root->children[0]->children[1]->value, 23);
	EXPECT_EQ(b_tree.root->children[1]->children[1]->children[0]->value, 83);
	EXPECT_EQ(b_tree.root->children[0]->children[1]->children[0]->value, 22);
	EXPECT_EQ(b_tree.root->children[1]->children[0]->value, 43);
	EXPECT_EQ(b_tree.root->children[0]->children[1]->children[1]->value, 28);
	EXPECT_EQ(b_tree.root->children[1]->children[0]->children[1]->value, 67);
	EXPECT_EQ(b_tree.root->children[1]->children[0]->children[1]->children[0]->value, 43);
	EXPECT_EQ(b_tree.root->children[1]->children[0]->children[0]->value, 30);

	c_binary_tree<int> b_tree_copy{ 20 };
	b_tree_copy = b_tree;//test copy constructor and copy assignment
	EXPECT_EQ(b_tree_copy.root->value, 30);
	EXPECT_EQ(b_tree_copy.root->children[0]->value, 12);
	EXPECT_EQ(b_tree_copy.root->children[1]->value, 72);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[1]->value, 109);
	EXPECT_EQ(b_tree_copy.root->children[0]->children[1]->value, 23);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[1]->children[0]->value, 83);
	EXPECT_EQ(b_tree_copy.root->children[0]->children[1]->children[0]->value, 22);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[0]->value, 43);
	EXPECT_EQ(b_tree_copy.root->children[0]->children[1]->children[1]->value, 28);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[0]->children[1]->value, 67);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[0]->children[1]->children[0]->value, 43);
	EXPECT_EQ(b_tree_copy.root->children[1]->children[0]->children[0]->value, 30);

	b_tree_copy.root->children[0]->value = 10;
	EXPECT_NE(b_tree.root->children[0]->value, b_tree_copy.root->children[0]->value);//proof they're different in memory

	//tree rotations!
	c_binary_tree<int> b_tree_need_l_r{ { 4, 6, 8 } };
	EXPECT_EQ(b_tree_need_l_r.root->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->children[1]->value, 8);
	b_tree_need_l_r.root = b_tree_need_l_r.rotate_left(b_tree_need_l_r.root);
	EXPECT_EQ(b_tree_need_l_r.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->value, 8);

	c_binary_tree<int> b_tree_need_r_r{ { 8, 6, 4 } };
	EXPECT_EQ(b_tree_need_r_r.root->value, 8);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->children[0]->value, 4);
	b_tree_need_r_r.root = b_tree_need_r_r.rotate_right(b_tree_need_r_r.root);
	EXPECT_EQ(b_tree_need_r_r.root->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_r_r.root->children[1]->value, 8);

	c_binary_tree<int> b_tree_need_l_r_rotate_two_calls{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[0]->children[1]->value, 6);
	b_tree_need_l_r_rotate_two_calls.root->children[0] = b_tree_need_l_r_rotate_two_calls.rotate_left(b_tree_need_l_r_rotate_two_calls.root->children[0]);//rotate on parent, not grandparent
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[0]->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[0]->children[0]->value, 4);
	b_tree_need_l_r_rotate_two_calls.root = b_tree_need_l_r_rotate_two_calls.rotate_right(b_tree_need_l_r_rotate_two_calls.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->children[1]->value, 8);

	c_binary_tree<int> b_tree_need_l_r_rotate_one_call{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->children[1]->value, 6);
	b_tree_need_l_r_rotate_one_call.root = b_tree_need_l_r_rotate_one_call.rotate_left_right(b_tree_need_l_r_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[1]->value, 8);

	c_binary_tree<int> b_tree_need_r_l_rotate_one_call{ { 4, 8, 6 } };
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->value, 8);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->children[0]->value, 6);
	b_tree_need_r_l_rotate_one_call.root = b_tree_need_r_l_rotate_one_call.rotate_right_left(b_tree_need_r_l_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->value, 8);

	c_binary_tree<int> b_tree_int_binary_funcs{ { 17, 77, 114, 28, 88, 27, 48, 33, 72, 48, 35 } };
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 27))->value, 27);
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 72))->value, 72);
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 77))->value, 77);
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 17))->value, 17);
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 8)), nullptr);
	EXPECT_EQ((*b_tree_int_binary_funcs.find_node(&b_tree_int_binary_funcs.root, 10050)), nullptr);

	EXPECT_EQ((*b_tree_int_binary_funcs.lca(&b_tree_int_binary_funcs.root, 88, 72))->value, 77);
	EXPECT_EQ((*b_tree_int_binary_funcs.lca(&b_tree_int_binary_funcs.root, 35, 72))->value, 48);
	EXPECT_EQ(*b_tree_int_binary_funcs.lca(&b_tree_int_binary_funcs.root, 38, 77), nullptr);//first value not in tree
	EXPECT_EQ(*b_tree_int_binary_funcs.lca(&b_tree_int_binary_funcs.root, 17, 200), nullptr);//second value not in tree

	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->children[1]->children[1]->children[0]->value), 4);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->children[1]->children[0]->children[0]->value), 4);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, 35), 6);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->value), 1);

	std::vector<c_poly_node<int>**> eithty_eight_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 88) };
	ASSERT_EQ(eithty_eight_path.size(), 4);
	std::array<int, 4> values_to_check_path1{ 17, 77, 114, 88 };
	for (size_t i{ 0 }; i < eithty_eight_path.size(); ++i)
		EXPECT_EQ((*eithty_eight_path[i])->value, values_to_check_path1[i]);
	std::vector<c_poly_node<int>**> seventy_two_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 72) };
	ASSERT_EQ(seventy_two_path.size(), 5);
	std::array<int, 5> values_to_check_path2{ 17, 77, 28, 48, 72 };
	for (size_t i{ 0 }; i < seventy_two_path.size(); ++i)
		EXPECT_EQ((*seventy_two_path[i])->value, values_to_check_path2[i]);
	std::vector<c_poly_node<int>**> seventeen_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 17) };//test root
	ASSERT_EQ(seventeen_path.size(), 1);
	EXPECT_EQ((*seventeen_path[0])->value, 17);

	c_binary_tree<int> b_tree_remove_simple{ { 4, 1, 8, 6, 3, 2 } };
	EXPECT_EQ(b_tree_remove_simple.root->children[0]->value, 1);
	EXPECT_EQ(b_tree_remove_simple.root->children[0]->children[1]->value, 3);
	EXPECT_EQ(b_tree_remove_simple.root->children[0]->children[1]->children[0]->value, 2);
	b_tree_remove_simple.remove_item(1);//see if tree is brought up with only right node
	EXPECT_EQ(b_tree_remove_simple.root->children[0]->value, 3);
	EXPECT_EQ(b_tree_remove_simple.root->children[0]->children[0]->value, 2);
	b_tree_remove_simple.remove_item(3);//see if left node is brought up
	b_tree_remove_simple.remove_item(8);//see if left tree is brought up
	b_tree_remove_simple.remove_item(6);//remove node by itself
	b_tree_remove_simple.remove_item(2);//remove last node from root
	EXPECT_EQ(b_tree_remove_simple.root->value, 4);//root is last lect
	EXPECT_EQ(b_tree_remove_simple.root->children[0], nullptr);
	EXPECT_EQ(b_tree_remove_simple.root->children[0], nullptr);
	b_tree_remove_simple.remove_item(4);
	EXPECT_EQ(b_tree_remove_simple.root, nullptr);

	c_binary_tree<int> b_tree_remove_complex{ { 5, 3, 7, 2, 4, 6, 8, 1, 9 } };
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->value, 3);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[0]->value, 2);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[1]->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[0]->children[0]->value, 1);
	b_tree_remove_complex.remove_item(3);//see if subtree's root can be removed
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[0]->value, 2);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[1], nullptr);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->children[0]->children[0]->value, 1);
	b_tree_remove_complex.remove_item(5);//see if root can be removed
	EXPECT_EQ(b_tree_remove_complex.root->value, 6);
	EXPECT_EQ(b_tree_remove_complex.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->children[1]->value, 7);
	EXPECT_EQ(b_tree_remove_complex.root->children[1]->children[0], nullptr);
	b_tree_remove_complex.remove_item(6);//checking that items in the tree become the new root in the correct order
	EXPECT_EQ(b_tree_remove_complex.root->value, 7);
	b_tree_remove_complex.remove_item(7);
	EXPECT_EQ(b_tree_remove_complex.root->value, 8);
	b_tree_remove_complex.remove_item(8);
	EXPECT_EQ(b_tree_remove_complex.root->value, 9);
	b_tree_remove_complex.remove_item(9);
	EXPECT_EQ(b_tree_remove_complex.root->value, 4);
	b_tree_remove_complex.remove_item(4);
	EXPECT_EQ(b_tree_remove_complex.root->value, 2);
	b_tree_remove_complex.remove_item(2);
	EXPECT_EQ(b_tree_remove_complex.root->value, 1);//check that all has been successfully deleted except root
	EXPECT_EQ(b_tree_remove_complex.root->children[0], nullptr);
	EXPECT_EQ(b_tree_remove_complex.root->children[1], nullptr);
}

TEST(c_avl_binary_tree_tests, c_avl_function_tests)
{
	c_avl_binary_tree<int, c_poly_node<int>> avl_height{ { 18, 5, 20 } };
	EXPECT_EQ(avl_height.height(avl_height.root), 2);
	EXPECT_EQ(avl_height.height(avl_height.root->children[0]), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->children[1]), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->children[0]->children[0]), 0);//nullptr height is 0

	//rotation diagram below
	c_avl_binary_tree<int> avl_int_tree_add_item_and_rebal{ 10 };
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 10);
	avl_int_tree_add_item_and_rebal.add_item(5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->value, 5);
	avl_int_tree_add_item_and_rebal.add_item(2);//right rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->value, 10);

	avl_int_tree_add_item_and_rebal.add_item(4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[1]->value, 4);
	avl_int_tree_add_item_and_rebal.add_item(3);//right left rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[0]->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[1]->value, 4);

	avl_int_tree_add_item_and_rebal.add_item(12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->value, 12);
	avl_int_tree_add_item_and_rebal.add_item(18);//left rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->value, 12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[0]->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[1]->value, 4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[0]->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->value, 18);

	avl_int_tree_add_item_and_rebal.add_item(15);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->children[0]->value, 15);
	avl_int_tree_add_item_and_rebal.add_item(17);//left right rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->value, 12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[0]->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[0]->children[1]->value, 4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[0]->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->value, 17);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->children[0]->value, 15);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->children[1]->children[1]->children[1]->value, 18);

	/*
		Tab sizes are different in VS compared to github
		 10				   5			right rotate on 10
		  /				  /\
		 5		->		 2 10
		/
		2

		 5					5			right left rotate on 2
		 /\					/\
		2 10		->		3 10
		\					/\
		 4					2 4
		/
		3

		5					  5			left rotate on 10
		/\					 / \
		3 10		->		3   12
		/\  \				/\  / \
		2 4  12				2 4 10 18
			\
			18

		  5					  5			left right rotate on 18
		 / \				 / \
		3   12		->		3   12
		/\  / \				/\  / \
		2 4 10 18			2 4 10 17
			/				/\
			15				15 18
			\
			17
	 */

	c_avl_binary_tree<int> avl_int_sorted_list{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
	EXPECT_EQ(avl_int_sorted_list.root->value, 4);
	EXPECT_EQ(avl_int_sorted_list.root->children[0]->value, 2);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->value, 8);
	EXPECT_EQ(avl_int_sorted_list.root->children[0]->children[0]->value, 1);
	EXPECT_EQ(avl_int_sorted_list.root->children[0]->children[1]->value, 3);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->children[0]->value, 6);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->children[1]->value, 9);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->children[0]->children[0]->value, 5);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->children[0]->children[1]->value, 7);
	EXPECT_EQ(avl_int_sorted_list.root->children[1]->children[1]->children[1]->value, 10);

	/*
		  4
		  /\
		 2  8
		/\  /\
		1 3 6 9
			/\ \
		   5  7 10
	 */

	 //c_avl_int_binary_tree functions are tested in c_binary_tree already ^

	 //same layout, with 10 added ^
	c_avl_binary_tree<int> avl_remove_rebalance{ { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 } };
	avl_remove_rebalance.remove_item(20);//remove leaf
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[1]->children[1], nullptr);
	avl_remove_rebalance.remove_item(19);//remove leaf, imbalance in 18, cause left right rotation on 18
	EXPECT_EQ(avl_remove_rebalance.root->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->value, 12);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[0]->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[1]->value, 13);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[0]->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[1]->value, 18);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[0]->children[0]->value, 15);

	avl_remove_rebalance.remove_item(12);//remove node with two children
	EXPECT_EQ(avl_remove_rebalance.root->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->value, 13);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[0]->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[0]->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[1]->value, 18);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[0]->children[0]->value, 15);

	avl_remove_rebalance.remove_item(13);//remove node with one left child, right left rotation on 14
	EXPECT_EQ(avl_remove_rebalance.root->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[0]->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[1]->value, 15);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->children[1]->value, 18);

	avl_remove_rebalance.remove_item(16);//delete root
	avl_remove_rebalance.remove_item(18);//delete node with just one right child, left right rotation on 17/root
	EXPECT_EQ(avl_remove_rebalance.root->value, 15);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->children[1]->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->children[0]->children[0]->value, 11);
}

TEST(c_heap_tests, c_max_and_min_heap_tests)
{
	EXPECT_EQ((c_heap<int, c_poly_node<int>, std::less<>>::amount_in_level(0)), 1);
	EXPECT_EQ((c_heap<int>::amount_in_level(1)), 2);
	EXPECT_EQ((c_heap<int>::amount_in_level(2)), 4);
	EXPECT_EQ((c_heap<int>::amount_in_level(3)), 8);

	EXPECT_EQ((c_heap<int>::amount_full_tree(1)), 1);
	EXPECT_EQ((c_heap<int>::amount_full_tree(2)), 3);
	EXPECT_EQ((c_heap<int>::amount_full_tree(3)), 7);
	EXPECT_EQ((c_heap<int>::amount_full_tree(4)), 15);

	EXPECT_EQ((c_heap<int>::amount_complete_levels(1)), 1);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(2)), 1);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(3)), 2);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(4)), 2);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(10)), 3);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(15)), 4);
	EXPECT_EQ((c_heap<int>::amount_complete_levels(7)), 3);

	EXPECT_EQ((c_heap<int>::amount_last_level(0)), 1);
	EXPECT_EQ((c_heap<int>::amount_last_level(1)), 0);
	EXPECT_EQ((c_heap<int>::amount_last_level(2)), 1);
	EXPECT_EQ((c_heap<int>::amount_last_level(3)), 0);
	EXPECT_EQ((c_heap<int>::amount_last_level(4)), 1);
	EXPECT_EQ((c_heap<int>::amount_last_level(5)), 2);
	EXPECT_EQ((c_heap<int>::amount_last_level(6)), 3);

	c_max_heap<int> max_heap_add{ 10 };
	EXPECT_EQ(max_heap_add.root->value, 10);
	EXPECT_EQ(max_heap_add.root->children[0], nullptr);
	EXPECT_EQ(max_heap_add.root->children[1], nullptr);

	max_heap_add.add_item(15);//swap 10 and 15
	EXPECT_EQ(max_heap_add.root->value, 15);
	EXPECT_EQ(max_heap_add.root->children[0]->value, 10);

	max_heap_add.add_item(19);//swap 15 and 19
	EXPECT_EQ(max_heap_add.root->value, 19);
	EXPECT_EQ(max_heap_add.root->children[0]->value, 10);
	EXPECT_EQ(max_heap_add.root->children[1]->value, 15);

	max_heap_add.add_item(32);//swap 10 and 32 then swap 19 and 32
	EXPECT_EQ(max_heap_add.root->value, 32);
	EXPECT_EQ(max_heap_add.root->children[0]->value, 19);
	EXPECT_EQ(max_heap_add.root->children[1]->value, 15);
	EXPECT_EQ(max_heap_add.root->children[0]->children[0]->value, 10);

	/*
		  32
		  /\
		 19 15
		 /
		10
	*/

	c_max_heap<int> larger_max_heap_remove{ { 10, 20, 50, 72, 19, 67, 5, 32, 48, 95, 140, 34, 18 } };
	EXPECT_EQ(larger_max_heap_remove.size, 13);
	EXPECT_EQ(larger_max_heap_remove.root->value, 140);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 95);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 67);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 72);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[1]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[1]->value, 50);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->children[0]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->children[0], nullptr);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 12);
	EXPECT_EQ(larger_max_heap_remove.root->value, 95);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 72);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 67);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 50);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[1]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->children[0]->value, 20);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 11);
	EXPECT_EQ(larger_max_heap_remove.root->value, 72);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 50);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 67);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[1]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[1]->value, 18);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 10);
	EXPECT_EQ(larger_max_heap_remove.root->value, 67);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 50);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[1]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->children[0]->value, 19);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 9);
	EXPECT_EQ(larger_max_heap_remove.root->value, 50);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[1]->value, 19);

	larger_max_heap_remove.remove_item();//causes trickle down case where right node is null and left node is less than parent where 19 is parent and 10 is left node
	EXPECT_EQ(larger_max_heap_remove.size, 8);
	EXPECT_EQ(larger_max_heap_remove.root->value, 48);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->children[0]->value, 10);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 7);
	EXPECT_EQ(larger_max_heap_remove.root->value, 34);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[1]->value, 5);

	larger_max_heap_remove.remove_item();//remove item with full last level
	EXPECT_EQ(larger_max_heap_remove.size, 6);
	EXPECT_EQ(larger_max_heap_remove.root->value, 32);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 5);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->children[0]->value, 10);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 5);
	EXPECT_EQ(larger_max_heap_remove.root->value, 20);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[1]->value, 5);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 4);
	EXPECT_EQ(larger_max_heap_remove.root->value, 19);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->children[0]->value, 5);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 3);
	EXPECT_EQ(larger_max_heap_remove.root->value, 18);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[1]->value, 5);

	larger_max_heap_remove.remove_item();
	EXPECT_EQ(larger_max_heap_remove.size, 2);
	EXPECT_EQ(larger_max_heap_remove.root->value, 10);
	EXPECT_EQ(larger_max_heap_remove.root->children[0]->value, 5);

	larger_max_heap_remove.remove_item();//remove item when only root and left child
	EXPECT_EQ(larger_max_heap_remove.size, 1);
	EXPECT_EQ(larger_max_heap_remove.root->value, 5);

	larger_max_heap_remove.remove_item();//remove just root
	EXPECT_EQ(larger_max_heap_remove.size, 0);
	EXPECT_EQ(larger_max_heap_remove.root, nullptr);

	//functions for min heap are the same as max with only the operator > or < changed
	c_min_heap<int> larger_min_heap_remove{ { 54, 11, 20, 82, 11, 73, 6, 38, 1, 48 } };//tests add, add_items, and trickle_up
	EXPECT_EQ(larger_min_heap_remove.root->value, 1);
	larger_min_heap_remove.remove_item();//tests trickle_down and remove_item
	EXPECT_EQ(larger_min_heap_remove.root->value, 6);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 11);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 11);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 20);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 38);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 48);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 54);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 73);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root->value, 82);
	larger_min_heap_remove.remove_item();
	EXPECT_EQ(larger_min_heap_remove.root, nullptr);
}

TEST(c_red_black_bst, c_red_black_bst_funcs_and_rebalancing)
{
	c_red_black_binary_tree<int, c_red_black_poly_node<int>> red_aunt_left_left{ { 15, 20, 10, 5 } };
	EXPECT_FALSE(red_aunt_left_left.root->children[1]->red);//check aunt
	EXPECT_FALSE(red_aunt_left_left.root->red);//root stays black
	EXPECT_FALSE(red_aunt_left_left.root->children[0]->red);
	EXPECT_TRUE(red_aunt_left_left.root->children[0]->children[0]->red);

	c_red_black_binary_tree<int> black_aunt_left_left{ { 15, 10, 5 } };
	EXPECT_FALSE(black_aunt_left_left.root->red);
	EXPECT_TRUE(black_aunt_left_left.root->children[0]->red);
	EXPECT_TRUE(black_aunt_left_left.root->children[1]->red);

	c_red_black_binary_tree<int> red_aunt_left_right{ { 15, 20, 5, 10 } };
	EXPECT_FALSE(red_aunt_left_right.root->children[1]->red);//check aunt
	EXPECT_FALSE(red_aunt_left_right.root->red);//root stays black
	EXPECT_FALSE(red_aunt_left_right.root->children[0]->red);
	EXPECT_TRUE(red_aunt_left_right.root->children[0]->children[1]->red);

	c_red_black_binary_tree<int> black_aunt_left_right{ { 15, 5, 10 } };
	EXPECT_FALSE(black_aunt_left_right.root->red);
	EXPECT_TRUE(black_aunt_left_right.root->children[0]->red);
	EXPECT_TRUE(black_aunt_left_right.root->children[1]->red);

	c_red_black_binary_tree<int> red_aunt_right_left{ { 10, 5, 20, 15 } };
	EXPECT_FALSE(red_aunt_right_left.root->children[0]->red);//check aunt
	EXPECT_FALSE(red_aunt_right_left.root->red);//root stays black
	EXPECT_FALSE(red_aunt_right_left.root->children[1]->red);
	EXPECT_TRUE(red_aunt_right_left.root->children[1]->children[0]->red);

	c_red_black_binary_tree<int> black_aunt_right_left{ { 10, 20, 15 } };
	EXPECT_FALSE(black_aunt_right_left.root->red);
	EXPECT_TRUE(black_aunt_right_left.root->children[0]->red);
	EXPECT_TRUE(black_aunt_right_left.root->children[1]->red);

	c_red_black_binary_tree<int> red_aunt_right_right{ { 10, 5, 15, 20 } };
	EXPECT_FALSE(red_aunt_right_right.root->children[0]->red);//check aunt
	EXPECT_FALSE(red_aunt_right_right.root->red);
	EXPECT_FALSE(red_aunt_right_right.root->children[1]->red);
	EXPECT_TRUE(red_aunt_right_right.root->children[1]->children[1]->red);

	c_red_black_binary_tree<int> black_aunt_right_right{ { 10, 15, 20 } };
	EXPECT_FALSE(black_aunt_right_right.root->red);//root stays black
	EXPECT_TRUE(black_aunt_right_right.root->children[0]->red);
	EXPECT_TRUE(black_aunt_right_right.root->children[1]->red);

	c_red_black_binary_tree<int> red_black_int_sorted_list{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
	EXPECT_EQ(red_black_int_sorted_list.root->value, 4);
	EXPECT_EQ(red_black_int_sorted_list.root->children[0]->value, 2);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->value, 6);
	EXPECT_EQ(red_black_int_sorted_list.root->children[0]->children[0]->value, 1);
	EXPECT_EQ(red_black_int_sorted_list.root->children[0]->children[1]->value, 3);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->children[0]->value, 5);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->children[1]->value, 8);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->children[1]->children[0]->value, 7);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->children[1]->children[1]->value, 9);
	EXPECT_EQ(red_black_int_sorted_list.root->children[1]->children[1]->children[1]->children[1]->value, 10);

	/*
		  4
		  /\
		 2  6
		/\  /\
		1 3 5 8
			  /\
			 7  9
				 \
				  10

	*Though it is not the same as the balanced avl tree, it is balanced correctly for a red black tree
	 */

	 //rotations and rebalancing remove_item tested in avl tests
}

/*
 * these are considered depth first search
 * in order traversal navigates all nodes in a normal bst in ascending order
 * left root right
 *
 * post order traversal
 * left right root
 *
 * preorder traversal
 * root left right
 *
 * level order traversal or breadth first search
 * left to right each level
 *
 * I'm kinda thinking that converting the tree into a 1D form to be traversed sounds easiest
 * but that's kinda incorrect
 * I should traverse the way that the structure is
 * THESE CANNOT RELY ON VALUES FOR NAVIGATION
 */

 /*
  * I should look into heap/tree merging
  */

TEST(c_linked_list_iterator, c_linked_list_iterator_operations)
{
	c_linked_list<int> only_head{ 10 };
	c_linked_list_iterator<int> only_head_and_end{ &only_head.head };
	EXPECT_EQ((**only_head_and_end)->value, 10);
	++only_head_and_end;
	EXPECT_EQ(**only_head_and_end, nullptr);

	c_linked_list<int> lots_to_navigate{ { 10, 8, 15, 19, 20, 13 } };
	c_linked_list_iterator<int> navigate_long_list{ &lots_to_navigate.head };
	EXPECT_EQ((**navigate_long_list)->value, 10);
	++navigate_long_list;
	EXPECT_EQ((**navigate_long_list)->value, 8);
	++navigate_long_list;
	EXPECT_EQ((**navigate_long_list)->value, 15);
	++navigate_long_list;
	EXPECT_EQ((**navigate_long_list)->value, 19);
	++navigate_long_list;
	EXPECT_EQ((**navigate_long_list)->value, 20);
	++navigate_long_list;
	EXPECT_EQ((**navigate_long_list)->value, 13);
	++navigate_long_list;
	EXPECT_EQ(**navigate_long_list, nullptr);

	std::vector<int> values_to_check{ 10, 8, 15, 19, 20, 13 };
	int index{ 0 };
	for (c_poly_node<int>** current : lots_to_navigate)//checking for for each compatibility, it uses begin(), end(), !=, *, and prefix of ++
	{
		EXPECT_EQ((*current)->value, values_to_check[index]);
		++index;
	}
}

TEST(c_linked_list, c_linked_list_funcs_and_tests)
{
	c_linked_list<int, c_poly_node<int>> one_param_constructor{ 5 };//testing the node specification
	EXPECT_EQ(one_param_constructor.length(), 1);//only head to count
	EXPECT_EQ((*one_param_constructor[0])->value, 5);
	(*one_param_constructor[0])->value = 10;
	EXPECT_EQ(one_param_constructor.head->value, 10);//original changed
	EXPECT_THROW(one_param_constructor[1], std::out_of_range);

	c_linked_list<int> many_vals_to_copy{ { 3, 6, 9 } };
	c_linked_list<int> copy{ many_vals_to_copy };//test copy constructor
	EXPECT_EQ(copy.head->value, 3);
	EXPECT_EQ(copy.head->children[0]->value, 6);
	EXPECT_EQ(copy.head->children[0]->children[0]->value, 9);
	copy.head->children[0]->children[0]->value = 18;
	EXPECT_NE(many_vals_to_copy.head->children[0]->children[0]->value, copy.head->children[0]->children[0]->value);//see if the change only happened to the copy

	copy = many_vals_to_copy;//test copy assignment operator
	EXPECT_EQ(copy.head->value, 3);
	EXPECT_EQ(copy.head->children[0]->value, 6);
	EXPECT_EQ(copy.head->children[0]->children[0]->value, 9);
	copy.head->children[0]->value = 25;
	EXPECT_NE(many_vals_to_copy.head->children[0]->value, copy.head->children[0]->value);//again, change occured only in copy

	c_linked_list<int> many_param_constructor_delete{ { 4, 10, 8, 2, 16 } };
	EXPECT_EQ(many_param_constructor_delete.length(), 5);//many items to count
	EXPECT_EQ(many_param_constructor_delete.head->value, 4);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->value, 10);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->value, 8);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->children[0]->value, 2);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->children[0]->children[0]->value, 16);
	EXPECT_EQ((*many_param_constructor_delete[0])->value, 4);
	EXPECT_EQ((*many_param_constructor_delete[1])->value, 10);
	EXPECT_EQ((*many_param_constructor_delete[2])->value, 8);
	EXPECT_EQ((*many_param_constructor_delete[3])->value, 2);
	EXPECT_EQ((*many_param_constructor_delete[4])->value, 16);

	many_param_constructor_delete.remove_item(8);//delete middle
	EXPECT_EQ(many_param_constructor_delete.head->value, 4);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->value, 10);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->value, 2);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->children[0]->value, 16);

	many_param_constructor_delete.remove_item_by_index(1);//delete middle by index
	EXPECT_EQ(many_param_constructor_delete.head->value, 4);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->value, 2);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->children[0]->value, 16);

	many_param_constructor_delete.remove_item(4);//delete head
	EXPECT_EQ(many_param_constructor_delete.head->value, 2);
	EXPECT_EQ(many_param_constructor_delete.head->children[0]->value, 16);

	many_param_constructor_delete.remove_item_by_index(0);//delete head by index
	EXPECT_EQ(many_param_constructor_delete.head->value, 16);

	many_param_constructor_delete.remove_item(16);//delete last item
	EXPECT_EQ(many_param_constructor_delete.length(), 0);//no items to count
	EXPECT_EQ(many_param_constructor_delete.head, nullptr);

	many_param_constructor_delete.add_item(24);
	many_param_constructor_delete.remove_item_by_index(0);//delete last item by index
	EXPECT_EQ(many_param_constructor_delete.length(), 0);//no items to count
	EXPECT_EQ(many_param_constructor_delete.head, nullptr);

	c_linked_list<int> occurrences{ { 4, 4, 4, 4, 5, 4, 4 } };
	EXPECT_EQ(occurrences.amount_reoccurs(4), 6);
	EXPECT_EQ(occurrences.amount_reoccurs(5), 1);
	EXPECT_EQ(occurrences.amount_reoccurs(15), 0);

	c_linked_list<int> check_loop{ { 1, 2, 3 } };
	EXPECT_FALSE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 0);//no loop
	(*check_loop[2])->children[0] = check_loop.head;//create loop by making last node's child = first element
	EXPECT_TRUE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 3);//loop with 3 elements inside
	(*check_loop[2])->children[0] = nullptr;//so that the destructor can delete this list correctly

	c_linked_list<int> check_loop_not_on_head{ { 1, 2, 3, 4, 5 } };
	EXPECT_FALSE(check_loop_not_on_head.detect_loop());
	EXPECT_EQ(check_loop_not_on_head.length_of_loop(), 0);//no loop
	(*check_loop_not_on_head[4])->children[0] = (*check_loop_not_on_head[2]);//create loop by making last node's child = first element
	EXPECT_TRUE(check_loop_not_on_head.detect_loop());
	EXPECT_EQ(check_loop_not_on_head.length_of_loop(), 3);//loop with 3 elements inside
	(*check_loop_not_on_head[4])->children[0] = nullptr;//so that the destructor can delete this list correctly*/

	c_linked_list<int> reverse_nodes{ { 5, 4, 3 } };
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 4);//test's that reverse worked once in middle section
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 5);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0], nullptr);
	reverse_nodes.add_item(6);//add item to end that will become the new head after another reverse
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 6);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 5);//test's that reverse worked twice in middle section
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 4);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->children[0], nullptr);
}

/*
 * unique pointers can't be shared
 * shared pointers have a reference count and delete when it reaches 0
 * weak pointers don't increase the reference count of shared pointers
 * if any don't point to anything anymore, they return nullptr?
 *
 * smart pointers are apparently not thread safe I think, which worries me a little
 */

 /*
  * Copying a heap would be easiest and most accurate with a level order iterator for the new and old heaps
  */

TEST(c_sorts, c_sort_header_tests)
{
	std::vector<int> small_duplicates_negatives_odd{ 1, 2, 4, 4, -4, 6, 7, -10, 10, 9, 10 };

	//all sorts of sorts
	std::vector<std::vector<int>& (*)(std::vector<int>&)> sorts{//vector of function pointers, same return type and same parameters
		c_bubble_sort<int>::sort,
		c_comb_sort<int>::sort,
		c_counting_sort<int>::sort,
		c_max_heap_sort<int>::sort,
		c_min_heap_sort<int>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::less<>, c_binary_tree<int, c_poly_node<int>>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::less<>, c_avl_binary_tree<int, c_poly_node<int>>>::sort,
		c_bst_sorts<int>::sort,
		c_merge_sort<int>::sort,
		c_quick_sort<int, 0>::sort,//leftmost pivot
		c_quick_sort<int>::sort,//default is 1, rightmost pivot
		c_quick_sort<int, 2>::sort,//middle pivot
		c_quick_sort<int, 3>::sort//random pivot
	};

	for (std::vector<int>& (*srt)(std::vector<int>&) : sorts)//for each sort function pointer
	{
		c_general_algorithms::scramble_vals(small_duplicates_negatives_odd);
		srt(small_duplicates_negatives_odd);
		for (int i{ 0 }; i < static_cast<int>(small_duplicates_negatives_odd.size()) - 1; ++i)//check that it's sorted
			EXPECT_LE(small_duplicates_negatives_odd[i], small_duplicates_negatives_odd[i + 1]);
		//testing::internal::SleepMilliseconds(1000);//you can add this line to let the random seed for scramble be different each second
	}

	//Now let's sort in reverse order
	std::vector<std::vector<int>& (*)(std::vector<int>&)> reverse_sorts{//vector of function pointers, same return type and same parameters
		c_bubble_sort<int, std::greater<>>::sort,
		c_comb_sort<int, std::greater<>>::sort,
		c_counting_sort<int, std::greater<>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::greater<>, c_binary_tree<int, c_poly_node<int>, std::greater<>>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::greater<>, c_avl_binary_tree<int, c_poly_node<int>, std::greater<>>>::sort,
		c_bst_sorts<int, c_red_black_poly_node<int>, std::greater<>, c_red_black_binary_tree<int, c_red_black_poly_node<int>, std::greater<>>>::sort,
		c_merge_sort<int, std::greater<>>::sort,
		c_quick_sort<int, 1, std::greater<>>::sort,
		c_heap_sort<int, c_poly_node<int>, std::greater<>>::sort//this is the same as a normal max heap sort, but I wanted to show it's possible to pass your own operations to this sort
	};

	for (std::vector<int>& (*srt)(std::vector<int>&) : reverse_sorts)//for each sort function pointer
	{
		c_general_algorithms::scramble_vals(small_duplicates_negatives_odd);
		srt(small_duplicates_negatives_odd);
		for (int i{ 0 }; i < static_cast<int>(small_duplicates_negatives_odd.size()) - 1; ++i)//check that it's sorted in reverse
			EXPECT_GE(small_duplicates_negatives_odd[i], small_duplicates_negatives_odd[i + 1]);
		//testing::internal::SleepMilliseconds(1000);//you can add this line to let the random seed for scramble be different each second
	}
}

int main(int argc, char* argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}