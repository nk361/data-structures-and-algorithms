#include "pch.h"

#include <vector>

#include "../../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../../D_S_and_A/Data Structures/c_binary_tree.h"
#include "../../../D_S_and_A/Data Structures/Iterators/c_bst_iterator_in_order.h"

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