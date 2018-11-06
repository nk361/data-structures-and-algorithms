#pragma once
#include <vector>
#include "c_max_heap_sort.h"

template<class MyType>
std::vector<MyType>& c_max_heap_sort<MyType>::sort(std::vector<MyType>& arr)
{
	c_max_heap<MyType, c_poly_node> heap{ arr[0] };
	for (int i{ 1 }; i < arr.size(); ++i)
		heap.add_item(arr[i]);
	for (int i{ static_cast<int>(arr.size()) - 1 }; i >= 0; --i)//go backward through array adding largest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}