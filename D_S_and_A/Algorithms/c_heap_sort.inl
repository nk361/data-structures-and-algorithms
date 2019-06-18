#pragma once

#include <vector>

#include "c_heap_sort.h"

//by default, this is the same as a min heap sort, but I made this so that other operations that min and max heap can't handle are available
template<class DataType, class NodeType, typename Operation>
std::vector<DataType>& c_heap_sort<DataType, NodeType, Operation>::sort(std::vector<DataType>& arr)
{
	c_heap<DataType, NodeType, Operation> heap{ arr[0] };
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)
		heap.add_item(arr[i]);
	for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i)//go forward through array adding smallest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}