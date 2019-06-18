#pragma once

#include <vector>

#include "../Data Structures/c_max_heap.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_max_heap_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_max_heap_sort.inl"