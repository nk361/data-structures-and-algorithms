#include "pch.h"

#include "../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_linked_list.h"

TEST(c_linked_list, c_linked_list_funcs_and_tests)
{
	c_linked_list<int, c_poly_node<int>> one_param_constructor{ 5 };//testing the node specification
	EXPECT_EQ(one_param_constructor.length(), 1);//only head to count
	EXPECT_EQ((*one_param_constructor[0])->value, 5);
	(*one_param_constructor[0])->value = 10;
	EXPECT_EQ(one_param_constructor.head->value, 10);//original changed
	EXPECT_THROW(one_param_constructor[1], std::out_of_range);

	c_linked_list<int> many_vals_to_copy{ { 3, 6, 9 } };
	c_linked_list<int> copy{ many_vals_to_copy };//test copy constructor
	EXPECT_EQ(copy.head->value, 3);
	EXPECT_EQ(copy.head->children[0]->value, 6);
	EXPECT_EQ(copy.head->children[0]->children[0]->value, 9);
	copy.head->children[0]->children[0]->value = 18;
	EXPECT_NE(many_vals_to_copy.head->children[0]->children[0]->value, copy.head->children[0]->children[0]->value);//see if the change only happened to the copy

	copy = many_vals_to_copy;//test copy assignment operator
	EXPECT_EQ(copy.head->value, 3);
	EXPECT_EQ(copy.head->children[0]->value, 6);
	EXPECT_EQ(copy.head->children[0]->children[0]->value, 9);
	copy.head->children[0]->value = 25;
	EXPECT_NE(many_vals_to_copy.head->children[0]->value, copy.head->children[0]->value);//again, change occured only in copy

	c_linked_list<int> many_param_constructor_delete{ { 4, 10, 8, 2, 16 } };
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

	c_linked_list<int> occurrences{ { 4, 4, 4, 4, 5, 4, 4 } };
	EXPECT_EQ(occurrences.amount_reoccurs(4), 6);
	EXPECT_EQ(occurrences.amount_reoccurs(5), 1);
	EXPECT_EQ(occurrences.amount_reoccurs(15), 0);

	c_linked_list<int> check_loop{ { 1, 2, 3 } };
	EXPECT_FALSE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 0);//no loop
	(*check_loop[2])->children[0] = check_loop.head;//create loop by making last node's child = first element
	EXPECT_TRUE(check_loop.detect_loop());
	EXPECT_EQ(check_loop.length_of_loop(), 3);//loop with 3 elements inside
	(*check_loop[2])->children[0] = nullptr;//so that the destructor can delete this list correctly

	c_linked_list<int> check_loop_not_on_head{ { 1, 2, 3, 4, 5 } };
	EXPECT_FALSE(check_loop_not_on_head.detect_loop());
	EXPECT_EQ(check_loop_not_on_head.length_of_loop(), 0);//no loop
	(*check_loop_not_on_head[4])->children[0] = (*check_loop_not_on_head[2]);//create loop by making last node's child = first element
	EXPECT_TRUE(check_loop_not_on_head.detect_loop());
	EXPECT_EQ(check_loop_not_on_head.length_of_loop(), 3);//loop with 3 elements inside
	(*check_loop_not_on_head[4])->children[0] = nullptr;//so that the destructor can delete this list correctly*/

	c_linked_list<int> reverse_nodes{ { 5, 4, 3 } };
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 4);//test's that reverse worked once in middle section
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 5);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0], nullptr);
	reverse_nodes.add_item(6);//add item to end that will become the new head after another reverse
	reverse_nodes.reverse();
	EXPECT_EQ(reverse_nodes.head->value, 6);
	EXPECT_EQ(reverse_nodes.head->children[0]->value, 5);//test's that reverse worked twice in middle section
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->value, 4);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->value, 3);
	EXPECT_EQ(reverse_nodes.head->children[0]->children[0]->children[0]->children[0], nullptr);
}