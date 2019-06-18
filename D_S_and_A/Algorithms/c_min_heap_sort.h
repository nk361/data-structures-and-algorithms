#pragma once

#include "../Data Structures/c_min_heap.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_min_heap_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_min_heap_sort.inl"