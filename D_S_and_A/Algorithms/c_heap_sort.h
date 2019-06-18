#pragma once

#include <vector>

#include "../Data Structures/c_heap.h"

template<class DataType, class NodeType = c_poly_node<DataType>, typename Operation = std::less<>>
class c_heap_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_heap_sort.inl"