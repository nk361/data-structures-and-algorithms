#pragma once
#include <vector>

#include "../Data Structures Headers/c_heap.h"

template<class MyType, template <class> class NodeType, typename Operation = std::less<>>
class c_heap_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_heap_sort.inl"