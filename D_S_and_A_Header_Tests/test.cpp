#include "pch.h"
#include "array"
#include "../D_S_and_A/Algorithms/c_general_algorithms.h"
#include "../D_S_and_A/Data Structures/c_node.h"
#include "../D_S_and_A/Data Structures/c_heap.h"
#include "../D_S_and_A/Data Structures/c_max_heap.h"
#include "../D_S_and_A/Data Structures/c_AVL_int_binary_tree.h"
#include "../D_S_and_A/Algorithms/c_bubble_sort.h"

TEST(GeneralAlgorithmsHeader, SmallGeneralAlgorithms)
{
	int sorted_array[]{ 1, 2, 3, 4, 5 };
	c_general_algorithms::scramble_array(sorted_array, sizeof(sorted_array) / sizeof(sorted_array[0]));
	EXPECT_FALSE(sorted_array[0] == 1 && sorted_array[1] == 2 && sorted_array[2] == 3 && sorted_array[3] == 4 && sorted_array[4] == 5);

	std::string sorted_strings[]{ "Amy", "Briana", "Cathy", "Darcy", "Emily", "Fatima", "Gretchen", "Hannah" };
	c_general_algorithms::scramble_array(sorted_strings, sizeof(sorted_strings) / sizeof(sorted_strings[0]));
	EXPECT_FALSE(sorted_strings[0] == "Amy" && sorted_strings[1] == "Briana" && sorted_strings[2] == "Cathy" && sorted_strings[3] == "Darcy" && sorted_strings[4] == "Emily" && sorted_strings[5] == "Fatima" && sorted_strings[6] == "Gretchen" && sorted_strings[7] == "Hannah");

	int values_to_sum[]{ 5, 2, 9, 8, 4, 10, 15 };
	std::pair<int, int> twelve = c_general_algorithms::pair_equal_to_sum(values_to_sum, sizeof(values_to_sum) / sizeof(values_to_sum[0]), 12);
	EXPECT_EQ(twelve.first, 8);
	EXPECT_EQ(twelve.second, 4);
	std::pair<int, int> nineteen = c_general_algorithms::pair_equal_to_sum(values_to_sum, sizeof(values_to_sum) / sizeof(values_to_sum[0]), 19);
	EXPECT_EQ(nineteen.first, 9);
	EXPECT_EQ(nineteen.second, 10);
	std::pair<int, int> twenty = c_general_algorithms::pair_equal_to_sum(values_to_sum, sizeof(values_to_sum) / sizeof(values_to_sum[0]), 20);
	EXPECT_EQ(twenty.first, 5);
	EXPECT_EQ(twenty.second, 15);
	std::pair<int, int> const fifty = c_general_algorithms::pair_equal_to_sum(values_to_sum, sizeof(values_to_sum) / sizeof(values_to_sum[0]), 50);
	EXPECT_TRUE(!fifty.first && !fifty.second);//Sum values not found
	
	//neither lamda function uses the index here, but still need to accept it to be called
	int(*multiply_sum)(int const&, int const&, int const&) = [](int const& index, int const& a, int const& b) { return a * b; };
	EXPECT_EQ(c_general_algorithms::capital_sigma(1, 5, multiply_sum, 10, 2), 100);

	double(*add_three)(int const&, double const&, double const&, double const&) = [](int const& index, double const& a, double const& b, double const& c) { return a + b + c; };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(1, 9, add_three, 5.5, 8.2, 10.7), 219.6);

	//lambda using the index
	double(*index_formula)(int const&, int const&) = [](int const& index, int const& x) { return pow(x, index + 2); };//x^(n + 2)
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(-3, 5, index_formula, 4), 21845.25);

	int(*sum_arrays)(int const&, std::vector<int> const&, std::vector<int> const&) = [](int const& index, std::vector<int> const& a, std::vector<int> const& b) { return a[index] * b[index]; };
	EXPECT_EQ(c_general_algorithms::capital_sigma(0, 2, sum_arrays, std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 4, 5, 6 }), 32);

	double(*multiply_this)(int const&, double const&, double const&, double const&) = [](int const& index, double const& a, double const& b, double const& c) { return a * index + b * index + c * index; };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_pi(1, 3, multiply_this, 5.0, 2.0, 3.0), 6000.0);
}

TEST(TreeNodeHeader, TreeNodeConstructors)
{
	c_node<int> number{ 5 };
	EXPECT_EQ(number.value, 5);
	EXPECT_EQ(number.left, nullptr);
	EXPECT_EQ(number.right, nullptr);

	c_node<std::string> word{ "Test" };
	EXPECT_STREQ(word.value.c_str(), "Test");
	EXPECT_EQ(word.left, nullptr);
	EXPECT_EQ(word.right, nullptr);
}

TEST(c_int_binary_treeTests, c_int_binary_treeFunctionTests)
{
	c_int_binary_tree<c_node> b_tree{ 30 };
	b_tree.add_items({ 12, 72, 109, 23, 83, 22, 43, 28, 67, 43, 30 });

	EXPECT_EQ(b_tree.root->value, 30);
	
	EXPECT_EQ(b_tree.root->left->value, 12);
	EXPECT_EQ(b_tree.root->right->value, 72);

	EXPECT_EQ(b_tree.root->right->right->value, 109);
	EXPECT_EQ(b_tree.root->left->right->value, 23);
	EXPECT_EQ(b_tree.root->right->right->left->value, 83);
	EXPECT_EQ(b_tree.root->left->right->left->value, 22);
	EXPECT_EQ(b_tree.root->right->left->value, 43);
	EXPECT_EQ(b_tree.root->left->right->right->value, 28);
	EXPECT_EQ(b_tree.root->right->left->right->value, 67);
	EXPECT_EQ(b_tree.root->right->left->right->left->value, 43);
	EXPECT_EQ(b_tree.root->right->left->left->value, 30);

	//tree rotations!
	c_int_binary_tree<c_node> b_tree_need_l_r{ { 4, 6, 8 } };
	EXPECT_EQ(b_tree_need_l_r.root->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->right->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->right->right->value, 8);
	b_tree_need_l_r.root = b_tree_need_l_r.rotate_left(b_tree_need_l_r.root);
	EXPECT_EQ(b_tree_need_l_r.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->right->value, 8);

	c_int_binary_tree<c_node> b_tree_need_r_r{ { 8, 6, 4 } };
	EXPECT_EQ(b_tree_need_r_r.root->value, 8);
	EXPECT_EQ(b_tree_need_r_r.root->left->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->left->left->value, 4);
	b_tree_need_r_r.root = b_tree_need_r_r.rotate_right(b_tree_need_r_r.root);
	EXPECT_EQ(b_tree_need_r_r.root->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->left->value, 4);
	EXPECT_EQ(b_tree_need_r_r.root->right->value, 8);

	c_int_binary_tree<c_node> b_tree_need_l_r_rotate_two_calls{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->left->right->value, 6);
	b_tree_need_l_r_rotate_two_calls.root->left = b_tree_need_l_r_rotate_two_calls.rotate_left(b_tree_need_l_r_rotate_two_calls.root->left);//rotate on parent, not grandparent
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->left->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->left->left->value, 4);
	b_tree_need_l_r_rotate_two_calls.root = b_tree_need_l_r_rotate_two_calls.rotate_right(b_tree_need_l_r_rotate_two_calls.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_two_calls.root->right->value, 8);

	c_int_binary_tree<c_node> b_tree_need_l_r_rotate_one_call{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->right->value, 6);
	b_tree_need_l_r_rotate_one_call.root = b_tree_need_l_r_rotate_one_call.rotate_left_right(b_tree_need_l_r_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->right->value, 8);

	c_int_binary_tree<c_node> b_tree_need_r_l_rotate_one_call{ { 4, 8, 6 } };
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->value, 8);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->left->value, 6);
	b_tree_need_r_l_rotate_one_call.root = b_tree_need_r_l_rotate_one_call.rotate_right_left(b_tree_need_r_l_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->value, 8);

	c_int_binary_tree<c_node> b_tree_int_binary_funcs{ { 17, 77, 114, 28, 88, 27, 48, 33, 72, 48, 35 } };
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

	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->right->right->left->value), 4);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->right->left->left->value), 4);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, 35), 6);
	EXPECT_EQ(b_tree_int_binary_funcs.depth(b_tree_int_binary_funcs.root, b_tree_int_binary_funcs.root->value), 1);

	std::vector<c_node<int> * *> eithty_eight_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 88) };
	ASSERT_EQ(eithty_eight_path.size(), 4);
	std::array<int, 4> values_to_check_path1{ 17, 77, 114, 88 };
	for (size_t i{ 0 }; i < eithty_eight_path.size(); ++i)
		EXPECT_EQ((*eithty_eight_path[i])->value, values_to_check_path1[i]);
	std::vector<c_node<int> * *> seventy_two_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 72) };
	ASSERT_EQ(seventy_two_path.size(), 5);
	std::array<int, 5> values_to_check_path2{ 17, 77, 28, 48, 72 };
	for (size_t i{ 0 }; i < seventy_two_path.size(); ++i)
		EXPECT_EQ((*seventy_two_path[i])->value, values_to_check_path2[i]);
	std::vector<c_node<int> * *> seventeen_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 17) };//test root
	ASSERT_EQ(seventeen_path.size(), 1);
	EXPECT_EQ((*seventeen_path[0])->value, 17);

	c_int_binary_tree<c_node> b_tree_remove_simple{ { 4, 1, 8, 6, 3, 2 } };
	EXPECT_EQ(b_tree_remove_simple.root->left->value, 1);
	EXPECT_EQ(b_tree_remove_simple.root->left->right->value, 3);
	EXPECT_EQ(b_tree_remove_simple.root->left->right->left->value, 2);
	b_tree_remove_simple.remove_item(1);//see if tree is brought up with only right node
	EXPECT_EQ(b_tree_remove_simple.root->left->value, 3);
	EXPECT_EQ(b_tree_remove_simple.root->left->left->value, 2);
	b_tree_remove_simple.remove_item(3);//see if left node is brought up
	b_tree_remove_simple.remove_item(8);//see if left tree is brought up
	b_tree_remove_simple.remove_item(6);//remove node by itself
	b_tree_remove_simple.remove_item(2);//remove last node from root
	EXPECT_EQ(b_tree_remove_simple.root->value, 4);//root is last lect
	EXPECT_EQ(b_tree_remove_simple.root->left, nullptr);
	EXPECT_EQ(b_tree_remove_simple.root->left, nullptr);
	b_tree_remove_simple.remove_item(4);
	EXPECT_EQ(b_tree_remove_simple.root, nullptr);

	c_int_binary_tree<c_node> b_tree_remove_complex{ { 5, 3, 7, 2, 4, 6, 8, 1, 9 } };
	EXPECT_EQ(b_tree_remove_complex.root->left->value, 3);
	EXPECT_EQ(b_tree_remove_complex.root->left->left->value, 2);
	EXPECT_EQ(b_tree_remove_complex.root->left->right->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->left->left->left->value, 1);
	b_tree_remove_complex.remove_item(3);//see if subtree's root can be removed
	EXPECT_EQ(b_tree_remove_complex.root->left->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->left->left->value, 2);
	EXPECT_EQ(b_tree_remove_complex.root->left->right, nullptr);
	EXPECT_EQ(b_tree_remove_complex.root->left->left->left->value, 1);
	b_tree_remove_complex.remove_item(5);//see if root can be removed
	EXPECT_EQ(b_tree_remove_complex.root->value, 6);
	EXPECT_EQ(b_tree_remove_complex.root->left->value, 4);
	EXPECT_EQ(b_tree_remove_complex.root->right->value, 7);
	EXPECT_EQ(b_tree_remove_complex.root->right->left, nullptr);
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
	EXPECT_EQ(b_tree_remove_complex.root->left, nullptr);
	EXPECT_EQ(b_tree_remove_complex.root->right, nullptr);
}

TEST(c_AVL_in_binary_tree_tests, c_AVL_function_tests)
{
	c_AVL_int_binary_tree<c_node> avl_height{ { 18, 5, 20 } };
	EXPECT_EQ(avl_height.height(avl_height.root), 2);
	EXPECT_EQ(avl_height.height(avl_height.root->left), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->right), 1);
	EXPECT_EQ(avl_height.height(avl_height.root->left->left), 0);//nullptr height is 0

	//rotation diagram below
	c_AVL_int_binary_tree<c_node> avl_int_tree_add_item_and_rebal{ 10 };
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 10);
	avl_int_tree_add_item_and_rebal.add_item(5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->value, 5);
	avl_int_tree_add_item_and_rebal.add_item(2);//right rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->value, 10);

	avl_int_tree_add_item_and_rebal.add_item(4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->right->value, 4);
	avl_int_tree_add_item_and_rebal.add_item(3);//right left rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->left->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->right->value, 4);

	avl_int_tree_add_item_and_rebal.add_item(12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->value, 12);
	avl_int_tree_add_item_and_rebal.add_item(18);//left rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->value, 12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->left->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->right->value, 4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->left->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->value, 18);

	avl_int_tree_add_item_and_rebal.add_item(15);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->left->value, 15);
	avl_int_tree_add_item_and_rebal.add_item(17);//left right rotation
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->value, 5);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->value, 3);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->value, 12);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->left->value, 2);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->left->right->value, 4);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->left->value, 10);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->value, 17);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->left->value, 15);
	EXPECT_EQ(avl_int_tree_add_item_and_rebal.root->right->right->right->value, 18);

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

	c_AVL_int_binary_tree<c_node> avl_int_sorted_list{ { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } };
	EXPECT_EQ(avl_int_sorted_list.root->value, 4);
	EXPECT_EQ(avl_int_sorted_list.root->left->value, 2);
	EXPECT_EQ(avl_int_sorted_list.root->right->value, 8);
	EXPECT_EQ(avl_int_sorted_list.root->left->left->value, 1);
	EXPECT_EQ(avl_int_sorted_list.root->left->right->value, 3);
	EXPECT_EQ(avl_int_sorted_list.root->right->left->value, 6);
	EXPECT_EQ(avl_int_sorted_list.root->right->right->value, 9);
	EXPECT_EQ(avl_int_sorted_list.root->right->left->left->value, 5);
	EXPECT_EQ(avl_int_sorted_list.root->right->left->right->value, 7);
	EXPECT_EQ(avl_int_sorted_list.root->right->right->right->value, 10);

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
	c_AVL_int_binary_tree<c_node> avl_remove_rebalance{ { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 } };
	avl_remove_rebalance.remove_item(20);//remove leaf
	EXPECT_EQ(avl_remove_rebalance.root->right->right->right, nullptr);
	avl_remove_rebalance.remove_item(19);//remove leaf, imbalance in 18, cause left right rotation on 18
	EXPECT_EQ(avl_remove_rebalance.root->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->left->value, 12);
	EXPECT_EQ(avl_remove_rebalance.root->right->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->left->left->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->left->right->value, 13);
	EXPECT_EQ(avl_remove_rebalance.root->right->left->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->right->right->value, 18);
	EXPECT_EQ(avl_remove_rebalance.root->right->left->left->value, 15);

	avl_remove_rebalance.remove_item(12);//remove node with two children
	EXPECT_EQ(avl_remove_rebalance.root->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->left->value, 13);
	EXPECT_EQ(avl_remove_rebalance.root->right->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->left->left->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->right->left->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->right->right->value, 18);
	EXPECT_EQ(avl_remove_rebalance.root->right->left->left->value, 15);

	avl_remove_rebalance.remove_item(13);//remove node with one left child, right left rotation on 14
	EXPECT_EQ(avl_remove_rebalance.root->value, 16);
	EXPECT_EQ(avl_remove_rebalance.root->left->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->right->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->left->left->value, 11);
	EXPECT_EQ(avl_remove_rebalance.root->left->right->value, 15);
	EXPECT_EQ(avl_remove_rebalance.root->right->right->value, 18);

	avl_remove_rebalance.remove_item(16);//delete root
	avl_remove_rebalance.remove_item(18);//delete node with just one right child, left right rotation on 17/root
	EXPECT_EQ(avl_remove_rebalance.root->value, 15);
	EXPECT_EQ(avl_remove_rebalance.root->left->value, 14);
	EXPECT_EQ(avl_remove_rebalance.root->right->value, 17);
	EXPECT_EQ(avl_remove_rebalance.root->left->left->value, 11);
}

TEST(c_max_heap_tests, c_max_heap_temp_function_tests)
{
	EXPECT_EQ(c_heap::amount_in_level(0), 1);
	EXPECT_EQ(c_heap::amount_in_level(1), 2);
	EXPECT_EQ(c_heap::amount_in_level(2), 4);
	EXPECT_EQ(c_heap::amount_in_level(3), 8);

	EXPECT_EQ(c_heap::amount_full_tree(1), 1);
	EXPECT_EQ(c_heap::amount_full_tree(2), 3);
	EXPECT_EQ(c_heap::amount_full_tree(3), 7);
	EXPECT_EQ(c_heap::amount_full_tree(4), 15);

	EXPECT_EQ(c_heap::amount_complete_levels(1), 1);
	EXPECT_EQ(c_heap::amount_complete_levels(2), 1);
	EXPECT_EQ(c_heap::amount_complete_levels(3), 2);
	EXPECT_EQ(c_heap::amount_complete_levels(4), 2);
	EXPECT_EQ(c_heap::amount_complete_levels(10), 3);
	EXPECT_EQ(c_heap::amount_complete_levels(15), 4);
	EXPECT_EQ(c_heap::amount_complete_levels(7), 3);

	EXPECT_EQ(c_heap::amount_last_level(0), 1);
	EXPECT_EQ(c_heap::amount_last_level(1), 0);
	EXPECT_EQ(c_heap::amount_last_level(2), 1);
	EXPECT_EQ(c_heap::amount_last_level(3), 0);
	EXPECT_EQ(c_heap::amount_last_level(4), 1);
	EXPECT_EQ(c_heap::amount_last_level(5), 2);
	EXPECT_EQ(c_heap::amount_last_level(6), 3);

	c_max_heap temp_tree{ 10 };
	EXPECT_EQ(temp_tree.root->value, 10);
	EXPECT_EQ(temp_tree.root->left, nullptr);
	EXPECT_EQ(temp_tree.root->right, nullptr);

	EXPECT_EQ(temp_tree.size, 1);
	EXPECT_EQ(temp_tree.amount_in_level(0), 1);
	EXPECT_EQ(temp_tree.amount_complete_levels(temp_tree.size), 1);

	temp_tree.add_item(15);
	EXPECT_EQ(temp_tree.root->value, 10);
	EXPECT_FALSE(temp_tree.root->left == nullptr);
	EXPECT_EQ(temp_tree.root->left->value, 15);
	EXPECT_EQ(temp_tree.root->right, nullptr);

	temp_tree.add_item(19);
	EXPECT_EQ(temp_tree.root->value, 10);
	EXPECT_EQ(temp_tree.root->left->value, 15);
	EXPECT_FALSE(temp_tree.root->right == nullptr);
	EXPECT_EQ(temp_tree.root->right->value, 19);

	temp_tree.add_item(32);
	EXPECT_EQ(temp_tree.root->value, 10);
	EXPECT_EQ(temp_tree.root->left->value, 15);
	EXPECT_EQ(temp_tree.root->right->value, 19);
	EXPECT_FALSE(temp_tree.root->left->left == nullptr);
	EXPECT_EQ(temp_tree.root->left->left->value, 32);

	/*
		
		10
		/\
		15 19
		/
	32
		
	*/

	c_max_heap larger_tree{ 10 };
	larger_tree.add_items({ 20, 50, 72, 19, 67, 5, 32, 48, 95, 140, 34, 18 });

	EXPECT_EQ(larger_tree.root->value, 10);//all these checks are before moving items up the tree
	EXPECT_EQ(larger_tree.root->left->left->left->value, 32);
	EXPECT_EQ(larger_tree.root->right->right->left, nullptr);
	EXPECT_EQ(larger_tree.root->right->right->right, nullptr);
	EXPECT_EQ(larger_tree.root->right->left->left->value, 34);
}

TEST(c_sorts, c_sort_header_tests)
{
	int small[]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	c_general_algorithms::scramble_array(small, 10);

	c_bubble_sort::sort(small, 10);
	for (int i = 0; i < 10 - 1; ++i)
		EXPECT_TRUE(small[i] <= small[i + 1]);
}

int main(int argc, char * argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}