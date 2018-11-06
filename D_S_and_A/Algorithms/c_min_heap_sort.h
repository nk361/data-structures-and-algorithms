#pragma once
#include "../Data Structures Headers/c_min_heap.h"

template<class MyType>
class c_min_heap_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_min_heap_sort.inl"