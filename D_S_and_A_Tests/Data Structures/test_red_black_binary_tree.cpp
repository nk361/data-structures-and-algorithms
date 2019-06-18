#include "pch.h"

#include "../../D_S_and_A/Data Structures/c_red_black_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_red_black_binary_tree.h"

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