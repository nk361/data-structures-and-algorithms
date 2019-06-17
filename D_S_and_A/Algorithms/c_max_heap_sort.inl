#pragma once
#include <vector>

#include "c_max_heap_sort.h"

template<class DataType, class NodeType>
std::vector<DataType>& c_max_heap_sort<DataType, NodeType>::sort(std::vector<DataType>& arr)
{
	c_max_heap<DataType, NodeType> heap{ arr[0] };
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)
		heap.add_item(arr[i]);
	for (int i{ static_cast<int>(arr.size()) - 1 }; i >= 0; --i)//go backward through array adding largest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}