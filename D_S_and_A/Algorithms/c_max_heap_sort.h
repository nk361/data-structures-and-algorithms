#pragma once
#include "../Data Structures Headers/c_max_heap.h"

template<class MyType>
class c_max_heap_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_max_heap_sort.inl"