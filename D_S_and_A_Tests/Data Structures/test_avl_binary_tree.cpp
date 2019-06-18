#include "pch.h"

#include "../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_avl_binary_tree.h"

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
				/					/\
				15					15 18
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