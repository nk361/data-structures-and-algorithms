#include "pch.h"

#include <vector>

#include "../../D_S_and_A/Algorithms/c_general_algorithms.h"

#include "../../D_S_and_A/Algorithms/c_bubble_sort.h"
#include "../../D_S_and_A/Algorithms/c_comb_sort.h"
#include "../../D_S_and_A/Algorithms/c_counting_sort.h"
#include "../../D_S_and_A/Algorithms/c_max_heap_sort.h"
#include "../../D_S_and_A/Algorithms/c_min_heap_sort.h"
#include "../../D_S_and_A/Algorithms/c_bst_sorts.h"
#include "../../D_S_and_A/Algorithms/c_merge_sort.h"
#include "../../D_S_and_A/Algorithms/c_quick_sort.h"
#include "../../D_S_and_A/Algorithms/c_heap_sort.h"

#include "../../D_S_and_A/Data Structures/c_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_avl_binary_tree.h"
#include "../../D_S_and_A/Data Structures/c_red_black_poly_node.h"
#include "../../D_S_and_A/Data Structures/c_red_black_binary_tree.h"

TEST(c_sorts, c_sort_header_tests)
{
	std::vector<int> small_duplicates_negatives_odd{ 1, 2, 4, 4, -4, 6, 7, -10, 10, 9, 10 };

	//all sorts of sorts
	std::vector<std::vector<int>& (*)(std::vector<int>&)> sorts{//vector of function pointers, same return type and same parameters
		c_bubble_sort<int>::sort,
		c_comb_sort<int>::sort,
		c_counting_sort<int>::sort,
		c_max_heap_sort<int>::sort,
		c_min_heap_sort<int>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::less<>, c_binary_tree<int, c_poly_node<int>>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::less<>, c_avl_binary_tree<int, c_poly_node<int>>>::sort,
		c_bst_sorts<int>::sort,
		c_merge_sort<int>::sort,
		c_quick_sort<int, 0>::sort,//leftmost pivot
		c_quick_sort<int>::sort,//default is 1, rightmost pivot
		c_quick_sort<int, 2>::sort,//middle pivot
		c_quick_sort<int, 3>::sort//random pivot
	};

	for (std::vector<int>& (*srt)(std::vector<int>&) : sorts)//for each sort function pointer
	{
		c_general_algorithms::scramble_vals(small_duplicates_negatives_odd);
		srt(small_duplicates_negatives_odd);
		for (int i{ 0 }; i < static_cast<int>(small_duplicates_negatives_odd.size()) - 1; ++i)//check that it's sorted
			EXPECT_LE(small_duplicates_negatives_odd[i], small_duplicates_negatives_odd[i + 1]);
		//testing::internal::SleepMilliseconds(1000);//you can add this line to let the random seed for scramble be different each second
	}

	//Now let's sort in reverse order
	std::vector<std::vector<int>& (*)(std::vector<int>&)> reverse_sorts{//vector of function pointers, same return type and same parameters
		c_bubble_sort<int, std::greater<>>::sort,
		c_comb_sort<int, std::greater<>>::sort,
		c_counting_sort<int, std::greater<>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::greater<>, c_binary_tree<int, c_poly_node<int>, std::greater<>>>::sort,
		c_bst_sorts<int, c_poly_node<int>, std::greater<>, c_avl_binary_tree<int, c_poly_node<int>, std::greater<>>>::sort,
		c_bst_sorts<int, c_red_black_poly_node<int>, std::greater<>, c_red_black_binary_tree<int, c_red_black_poly_node<int>, std::greater<>>>::sort,
		c_merge_sort<int, std::greater<>>::sort,
		c_quick_sort<int, 1, std::greater<>>::sort,
		c_heap_sort<int, c_poly_node<int>, std::greater<>>::sort//this is the same as a normal max heap sort, but I wanted to show it's possible to pass your own operations to this sort
	};

	for (std::vector<int>& (*srt)(std::vector<int>&) : reverse_sorts)//for each sort function pointer
	{
		c_general_algorithms::scramble_vals(small_duplicates_negatives_odd);
		srt(small_duplicates_negatives_odd);
		for (int i{ 0 }; i < static_cast<int>(small_duplicates_negatives_odd.size()) - 1; ++i)//check that it's sorted in reverse
			EXPECT_GE(small_duplicates_negatives_odd[i], small_duplicates_negatives_odd[i + 1]);
		//testing::internal::SleepMilliseconds(1000);//you can add this line to let the random seed for scramble be different each second
	}
}