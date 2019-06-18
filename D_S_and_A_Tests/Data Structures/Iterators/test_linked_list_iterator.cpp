#include "pch.h"

#include <vector>

#include "../../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../../D_S_and_A/Data Structures/c_linked_list.h"
#include "../../../D_S_and_A/Data Structures/Iterators/c_linked_list_iterator.h"

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