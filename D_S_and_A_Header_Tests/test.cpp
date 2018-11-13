#include "pch.h"
#include <array>
#include "../D_S_and_A/Algorithms/c_general_algorithms.h"
#include "../D_S_and_A/Data Structures Headers/c_poly_node.h"
#include "../D_S_and_A/Data Structures Headers/c_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_binary_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_AVL_binary_tree.h"
#include "../D_S_and_A/Data Structures Headers/c_heap.h"
#include "../D_S_and_A/Data Structures Headers/c_max_heap.h"
#include "../D_S_and_A/Data Structures Headers/c_min_heap.h"
#include "../D_S_and_A/Algorithms/c_bubble_sort.h"
#include "../D_S_and_A/Algorithms/c_counting_sort.h"
#include "../D_S_and_A/Algorithms/c_max_heap_sort.h"
#include "../D_S_and_A/Algorithms/c_min_heap_sort.h"
#include "../D_S_and_A/Data Structures Headers/c_linked_list.h"

TEST(GeneralAlgorithmsHeader, SmallGeneralAlgorithms)
{
	std::vector<int> sorted_vector{ 1, 2, 3, 4, 5 };
	c_general_algorithms::scramble_vals(sorted_vector);
	EXPECT_FALSE(sorted_vector[0] == 1 && sorted_vector[1] == 2 && sorted_vector[2] == 3 && sorted_vector[3] == 4 && sorted_vector[4] == 5);

	std::vector<std::string> sorted_strings{ "Amy", "Briana", "Cathy", "Darcy", "Emily", "Fatima", "Gretchen", "Hannah" };
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
	
	//neither lamda function uses the index here, but still need to accept it to be called
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
}

TEST(node_header_tests, TreeNodeConstructors)
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

	//letter.children[1] = &letter2;//lol didn't consider that I need a tree destructor to get rid of this
	//EXPECT_EQ(letter.children[0], nullptr);
	//EXPECT_EQ(letter.children[1]->value, 'f');
	//EXPECT_EQ(letter.children[2], nullptr);
	//EXPECT_EQ(letter.children[3], nullptr);
	//EXPECT_EQ(letter.children[4], nullptr);
}

TEST(c_binary_treeTests, c_binary_treeFunctionTests)
{
	c_binary_tree<int, c_poly_node> b_tree{ 30 };
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

	//tree rotations!
	c_binary_tree<int, c_poly_node> b_tree_need_l_r{ { 4, 6, 8 } };
	EXPECT_EQ(b_tree_need_l_r.root->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->children[1]->value, 8);
	b_tree_need_l_r.root = b_tree_need_l_r.rotate_left(b_tree_need_l_r.root);
	EXPECT_EQ(b_tree_need_l_r.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->children[1]->value, 8);

	c_binary_tree<int, c_poly_node> b_tree_need_r_r{ { 8, 6, 4 } };
	EXPECT_EQ(b_tree_need_r_r.root->value, 8);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->children[0]->value, 4);
	b_tree_need_r_r.root = b_tree_need_r_r.rotate_right(b_tree_need_r_r.root);
	EXPECT_EQ(b_tree_need_r_r.root->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_r_r.root->children[1]->value, 8);

	c_binary_tree<int, c_poly_node> b_tree_need_l_r_rotate_two_calls{ { 8, 4, 6 } };
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

	c_binary_tree<int, c_poly_node> b_tree_need_l_r_rotate_one_call{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->children[1]->value, 6);
	b_tree_need_l_r_rotate_one_call.root = b_tree_need_l_r_rotate_one_call.rotate_left_right(b_tree_need_l_r_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->children[1]->value, 8);

	c_binary_tree<int, c_poly_node> b_tree_need_r_l_rotate_one_call{ { 4, 8, 6 } };
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->value, 8);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->children[0]->value, 6);
	b_tree_need_r_l_rotate_one_call.root = b_tree_need_r_l_rotate_one_call.rotate_right_left(b_tree_need_r_l_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[0]->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->children[1]->value, 8);

	c_binary_tree<int, c_poly_node> b_tree_int_binary_funcs{ { 17, 77, 114, 28, 88, 27, 48, 33, 72, 48, 35 } };
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

	std::vector<c_poly_node<int> * *> eithty_eight_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 88) };
	ASSERT_EQ(eithty_eight_path.size(), 4);
	std::array<int, 4> values_to_check_path1{ 17, 77, 114, 88 };
	for (size_t i{ 0 }; i < eithty_eight_path.size(); ++i)
		EXPECT_EQ((*eithty_eight_path[i])->value, values_to_check_path1[i]);
	std::vector<c_poly_node<int> * *> seventy_two_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 72) };
	ASSERT_EQ(seventy_two_path.size(), 5);
	std::array<int, 5> values_to_check_path2{ 17, 77, 28, 48, 72 };
	for (size_t i{ 0 }; i < seventy_two_path.size(); ++i)
		EXPECT_EQ((*seventy_two_path[i])->value, values_to_check_path2[i]);
	std::vector<c_poly_node<int> * *> seventeen_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 17) };//test root
	ASSERT_EQ(seventeen_path.size(), 1);
	EXPECT_EQ((*seventeen_path[0])->value, 17);

	c_binary_tree<int, c_poly_node> b_tree_remove_simple{ { 4, 1, 8, 6, 3, 2 } };
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

	c_binary_tree<int, c_poly_node> b_tree_remove_complex{ { 5, 3, 7, 2, 4, 6, 8, 1, 9 } };
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

TEST(c_AVL_in_binary_tree_tests, c_AVL_function_tests)
{
	c_AVL_binary_tree<int, c_poly_node> avl_height{ { 18, 5, 20 } };
	EXPECT_EQ(avl_height.height(avl_height.root), 2);
	EXPECT_EQ(avl_height.height(avl_height.root->children[0]), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->children[1]), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->children[0]->children[0]), 0);//nullptr height is 0

	//rotation diagram below
	c_AVL_binary_tree<int, c_poly_node> avl_int_tree_add_item_and_rebal{ 10 };
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
			Tab sizes are different in VS than github
	      10			   5			right rotate on 10
		  /				  /\
		 5			->	 2 10
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
			   /				   /\
			  15				  15 18
			   \
				17
	 */

	c_AVL_binary_tree<int, c_poly_node> avl_int_sorted_list{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
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

	//c_AVL_int_binary_tree functions are tested in c_int_binary_tree already ^

	//same layout, with 10 added ^
	c_AVL_binary_tree<int, c_poly_node> avl_remove_rebalance{ { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 } };
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
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_in_level(0)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_in_level(1)), 2);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_in_level(2)), 4);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_in_level(3)), 8);

	EXPECT_EQ((c_heap<int, c_poly_node>::amount_full_tree(1)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_full_tree(2)), 3);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_full_tree(3)), 7);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_full_tree(4)), 15);

	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(1)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(2)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(3)), 2);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(4)), 2);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(10)), 3);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(15)), 4);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_complete_levels(7)), 3);

	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(0)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(1)), 0);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(2)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(3)), 0);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(4)), 1);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(5)), 2);
	EXPECT_EQ((c_heap<int, c_poly_node>::amount_last_level(6)), 3);

	c_max_heap<int, c_poly_node> max_heap_add{ 10 };
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

	c_max_heap<int, c_poly_node> larger_max_heap_remove{ { 10, 20, 50, 72, 19, 67, 5, 32, 48, 95, 140, 34, 18 } };
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
	c_min_heap<int, c_poly_node> larger_min_heap_remove{ { 54, 11, 20, 82, 11, 73, 6, 38, 1, 48 } };//tests add, add_items, and trickle_up
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

TEST(c_linked_list, c_linked_list_funcs_and_tests)
{
	c_linked_list<int, c_poly_node> one_param_constructor{ 5 };
	EXPECT_EQ(one_param_constructor.length(), 1);//only head to count
	EXPECT_EQ((*one_param_constructor[0])->value, 5);
	(*one_param_constructor[0])->value = 10;
	EXPECT_EQ(one_param_constructor.head->value, 10);//original changed
	EXPECT_THROW(one_param_constructor[1], std::out_of_range);

	c_linked_list<int, c_poly_node> many_param_constructor_delete{ { 4, 10, 8, 2, 16 } };
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

	c_linked_list<int, c_poly_node> occurances{ { 4, 4, 4, 4, 5, 4, 4 } };
	EXPECT_EQ(occurances.amount_reoccurs(4), 6);
	EXPECT_EQ(occurances.amount_reoccurs(5), 1);
	EXPECT_EQ(occurances.amount_reoccurs(15), 0);

	c_linked_list<int, c_poly_node> check_loop{ { 1, 2, 3 } };
	EXPECT_FALSE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 0);//no loop
	(*check_loop[2])->children[0] = check_loop.head;//create loop by making last node's child = first element
	EXPECT_TRUE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 3);//loop with 3 elements inside
	(*check_loop[2])->children[0] = nullptr;//so that the destructor can delete this list correctly

	c_linked_list<int, c_poly_node> reverse_nodes{ { 5, 4, 3 } };
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 4);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 5);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0], nullptr);
	reverse_nodes.add_item(6);//add item to end that will become the new head after another reverse
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 6);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 5);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 4);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->children[0], nullptr);
}

TEST(c_sorts, c_sort_header_tests)
{
	std::vector<int> small_duplicates_negatives{ 1, 2, 4, 4, -4, 6, 7, -10, 10, 9, 10 };

	std::vector<std::vector<int>& (*)(std::vector<int>&)> sorts{ //vector of function pointers, same return type and same parameters
		c_bubble_sort<int>::sort,
		c_counting_sort<int>::sort,
		c_max_heap_sort<int>::sort,
		c_min_heap_sort<int>::sort
	};

	for(std::vector<int>& (*srt)(std::vector<int>&) : sorts)//for each sort function pointer
	{
		c_general_algorithms::scramble_vals(small_duplicates_negatives);
		srt(small_duplicates_negatives);
		for (int i{ 0 }; i < small_duplicates_negatives.size() - 1; ++i)//check that it's sorted
			EXPECT_TRUE(small_duplicates_negatives[i] <= small_duplicates_negatives[i + 1]);
	}
}

int main(int argc, char * argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}