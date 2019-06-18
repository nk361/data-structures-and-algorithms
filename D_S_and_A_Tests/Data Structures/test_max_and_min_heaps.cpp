#include "pch.h"

#include "../../D_S_and_A/Data Structures/c_max_heap.h"
#include "../../D_S_and_A/Data Structures/c_min_heap.h"

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