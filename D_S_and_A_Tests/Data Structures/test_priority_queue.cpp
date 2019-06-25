#include "pch.h"

#include "../../D_S_and_A/Data Structures/c_max_heap.h"
#include "../../D_S_and_A/Data Structures/c_min_heap.h"
#include "../../D_S_and_A/Data Structures/c_priority_queue.h"

TEST(c_priority_queue, c_priority_queue_header_tests)
{
	c_priority_queue<int, c_max_heap<int>> using_max_binomial_heap{ 10 };
	EXPECT_EQ(using_max_binomial_heap.get_top(), 10);
	using_max_binomial_heap.add_item(20);
	EXPECT_EQ(using_max_binomial_heap.get_top(), 20);
	using_max_binomial_heap.add_items({ 5, 30, 2, 45, 23 });
	EXPECT_EQ(using_max_binomial_heap.get_top(), 45);
	using_max_binomial_heap.remove_item();
	EXPECT_EQ(using_max_binomial_heap.get_top(), 30);

	c_priority_queue<double, c_min_heap<double>> using_min_binomial_heap{ 10.1 };
	EXPECT_EQ(using_min_binomial_heap.get_top(), 10.1);
	using_min_binomial_heap.add_item(20.2);
	EXPECT_EQ(using_min_binomial_heap.get_top(), 10.1);
	using_min_binomial_heap.add_items({ 5.5, 30.3, 2.2, 45.4, 23.2 });
	EXPECT_EQ(using_min_binomial_heap.get_top(), 2.2);
	using_min_binomial_heap.remove_item();
	EXPECT_EQ(using_min_binomial_heap.get_top(), 5.5);
}