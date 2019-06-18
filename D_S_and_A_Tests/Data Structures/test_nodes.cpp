#include "pch.h"

#include <string>

#include "../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_red_black_poly_node.h"

TEST(c_node_header_tests, c_tree_node_constructors)
{
	c_poly_node<int> number{ 5, 2 };
	EXPECT_EQ(number.value, 5);
	EXPECT_EQ(number.children[0], nullptr);
	EXPECT_EQ(number.children[1], nullptr);

	c_poly_node<std::string> word{ "Test", 2 };
	EXPECT_STREQ(word.value.c_str(), "Test");
	EXPECT_EQ(word.children[0], nullptr);
	EXPECT_EQ(word.children[1], nullptr);

	c_poly_node<char> letter{ 'c', 5 };
	EXPECT_EQ(letter.value, 'c');
	EXPECT_EQ(letter.children[0], nullptr);
	EXPECT_EQ(letter.children[1], nullptr);
	EXPECT_EQ(letter.children[2], nullptr);
	EXPECT_EQ(letter.children[3], nullptr);
	EXPECT_EQ(letter.children[4], nullptr);

	c_poly_node<double> decimal{ 0.4, 7 };
	EXPECT_DOUBLE_EQ(decimal.value, 0.4);
	EXPECT_EQ(decimal.children[0], nullptr);
	EXPECT_EQ(decimal.children[1], nullptr);
	EXPECT_EQ(decimal.children[2], nullptr);
	EXPECT_EQ(decimal.children[3], nullptr);
	EXPECT_EQ(decimal.children[4], nullptr);
	EXPECT_EQ(decimal.children[5], nullptr);
	EXPECT_EQ(decimal.children[6], nullptr);

	c_red_black_poly_node<int> red_black{ 5, 2, false };
	EXPECT_EQ(red_black.value, 5);
	EXPECT_EQ(red_black.children[0], nullptr);
	EXPECT_EQ(red_black.children[1], nullptr);
	EXPECT_FALSE(red_black.red);
	red_black.red = true;
	EXPECT_TRUE(red_black.red);
}