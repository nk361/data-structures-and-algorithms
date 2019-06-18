#pragma once

#include <vector>

#include "c_min_heap_sort.h"

template<class DataType, class NodeType>
std::vector<DataType>& c_min_heap_sort<DataType, NodeType>::sort(std::vector<DataType>& arr)
{
	c_min_heap<DataType, NodeType> heap{ arr[0] };
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)
		heap.add_item(arr[i]);
	for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i)//go forward through array adding smallest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}
