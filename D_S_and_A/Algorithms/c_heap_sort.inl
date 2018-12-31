#pragma once
#include <vector>

#include "c_heap_sort.h"

//by default, this is the same as a min heap sort, but I made this so that other operations that min and max heap can't handle are available
template<class MyType, template <class> class NodeType, typename Operation>
std::vector<MyType>& c_heap_sort<MyType, NodeType, Operation>::sort(std::vector<MyType>& arr)
{
	c_heap<MyType, NodeType, Operation> heap{ arr[0] };
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)
		heap.add_item(arr[i]);
	for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i)//go forward through array adding smallest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}