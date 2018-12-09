#pragma once
#include <vector>

#include "c_min_heap_sort.h"

template<class MyType, template <class> class NodeType>
std::vector<MyType>& c_min_heap_sort<MyType, NodeType>::sort(std::vector<MyType>& arr)
{
	c_min_heap<MyType, NodeType> heap{ arr[0] };
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)
		heap.add_item(arr[i]);
	for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i)//go forward through array adding smallest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}
