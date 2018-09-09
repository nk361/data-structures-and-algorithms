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
	test_destructor_four.add_item(74);//an infinite loop is entered when a tree tries to add a fourth item or maybe tries to destroy it
}

TEST(c_max_heapTests, c_max_heapTempFunctionTests)
{
	//c_heap testing{ 30 };

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
}

int main(int argc, char * argv[])//char **argv
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}