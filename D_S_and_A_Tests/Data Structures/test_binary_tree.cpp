#include "pch.h"

#include <array>
#include <vector>

#include "../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_binary_tree.h"

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

	std::vector<c_poly_node<int>**> eighty_eight_path{ b_tree_int_binary_funcs.find_node_with_path(&b_tree_int_binary_funcs.root, 88) };
	ASSERT_EQ(eighty_eight_path.size(), 4);
	std::array<int, 4> values_to_check_path1{ 17, 77, 114, 88 };
	for (size_t i{ 0 }; i < eighty_eight_path.size(); ++i)
		EXPECT_EQ((*eighty_eight_path[i])->value, values_to_check_path1[i]);
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