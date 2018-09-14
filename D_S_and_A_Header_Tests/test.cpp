#include "pch.h"
#include "../D_S_and_A/c_node.h"
#include "../D_S_and_A/c_heap.h"
#include "../D_S_and_A/c_max_heap.h"

TEST(TreeNodeHeader, TreeNodeConstructors)
{
	c_node<int> number{ 5 };
	EXPECT_EQ(number.value, 5);
	EXPECT_EQ(number.left, nullptr);
	EXPECT_EQ(number.right, nullptr);

	c_node<std::string> string{ "Test" };
	EXPECT_STREQ(string.value.c_str(), "Test");
	EXPECT_EQ(string.left, nullptr);
	EXPECT_EQ(string.right, nullptr);
}

TEST(TreeHeader, TreeConstructors)
{
	c_max_heap test_destructor{ 45 };

	c_max_heap test_destructor_two{ 32 };
	test_destructor_two.add_item(65);

	c_max_heap test_destructor_three{ 15 };
	test_destructor_three.add_item(70);
	test_destructor_three.add_item(43);

	c_max_heap test_destructor_four{ 20 };
	test_destructor_four.add_item(67);
	test_destructor_four.add_item(19);
	test_destructor_four.add_item(74);
}

TEST(c_int_binary_treeTests, c_int_binary_treeFunctionTests)
{
	c_int_binary_tree b_tree{ 30 };
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
	c_int_binary_tree b_tree_need_l_r{ { 4, 6, 8 } };
	EXPECT_EQ(b_tree_need_l_r.root->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->right->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->right->right->value, 8);
	b_tree_need_l_r.root = b_tree_need_l_r.rotate_left(b_tree_need_l_r.root);
	EXPECT_EQ(b_tree_need_l_r.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r.root->right->value, 8);

	c_int_binary_tree b_tree_need_r_r{ { 8, 6, 4 } };
	EXPECT_EQ(b_tree_need_r_r.root->value, 8);
	EXPECT_EQ(b_tree_need_r_r.root->left->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->left->left->value, 4);
	b_tree_need_r_r.root = b_tree_need_r_r.rotate_right(b_tree_need_r_r.root);
	EXPECT_EQ(b_tree_need_r_r.root->value, 6);
	EXPECT_EQ(b_tree_need_r_r.root->left->value, 4);
	EXPECT_EQ(b_tree_need_r_r.root->right->value, 8);

	c_int_binary_tree b_tree_need_l_r_rotate_two_calls{ { 8, 4, 6 } };
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

	c_int_binary_tree b_tree_need_l_r_rotate_one_call{ { 8, 4, 6 } };
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 8);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->right->value, 6);
	b_tree_need_l_r_rotate_one_call.root = b_tree_need_l_r_rotate_one_call.rotate_left_right(b_tree_need_l_r_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_l_r_rotate_one_call.root->right->value, 8);

	c_int_binary_tree b_tree_need_r_l_rotate_one_call{ { 4, 8, 6 } };
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->value, 8);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->left->value, 6);
	b_tree_need_r_l_rotate_one_call.root = b_tree_need_r_l_rotate_one_call.rotate_right_left(b_tree_need_r_l_rotate_one_call.root);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->value, 6);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->left->value, 4);
	EXPECT_EQ(b_tree_need_r_l_rotate_one_call.root->right->value, 8);

	c_int_binary_tree b_tree_find_node{ { 17, 77, 114, 28, 88, 27, 48, 33, 72, 48, 35 } };
	EXPECT_EQ((*b_tree_find_node.find_node(27))->value, 27);
	EXPECT_EQ((*b_tree_find_node.find_node(72))->value, 72);
	EXPECT_EQ((*b_tree_find_node.find_node(77))->value, 77);
	EXPECT_EQ((*b_tree_find_node.find_node(17))->value, 17);
	EXPECT_EQ((*b_tree_find_node.find_node(8)), nullptr);
	EXPECT_EQ((*b_tree_find_node.find_node(10050)), nullptr);

	c_int_binary_tree b_tree_remove_simple{ { 4, 1, 8, 6, 3, 2 } };
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

	c_int_binary_tree b_tree_remove_complex{ { 5, 3, 7, 2, 4, 6, 8, 1, 9 } };
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

TEST(c_max_heapTests, c_max_heapTempFunctionTests)
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

	EXPECT_EQ(c_heap::amount_last_level(1), 0);
	EXPECT_EQ(c_heap::amount_last_level(2), 1);
	EXPECT_EQ(c_heap::amount_last_level(3), 0);
	EXPECT_EQ(c_heap::amount_last_level(4), 1);
	EXPECT_EQ(c_heap::amount_last_level(5), 2);
	EXPECT_EQ(c_heap::amount_last_level(6), 3);

	{
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
	}

	{
		c_max_heap larger_tree{ 10 };
		larger_tree.add_items({ 20, 50, 72, 19, 67, 5, 32, 48, 95, 140, 34, 18 });

		EXPECT_EQ(larger_tree.root->value, 10);//all these checks are before moving items up the tree
		EXPECT_EQ(larger_tree.root->left->left->left->value, 32);
		EXPECT_EQ(larger_tree.root->right->right->left, nullptr);
		EXPECT_EQ(larger_tree.root->right->right->right, nullptr);
		EXPECT_EQ(larger_tree.root->right->left->left->value, 34);
	}
}

int main(int argc, char * argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}