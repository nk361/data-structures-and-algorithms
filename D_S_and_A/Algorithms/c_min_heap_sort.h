#pragma once
#include "../Data Structures Headers/c_min_heap.h"

template<class MyType>
class c_min_heap_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

template<class MyType>
std::vector<MyType>& c_min_heap_sort<MyType>::sort(std::vector<MyType>& arr)
{
	c_min_heap<MyType, c_poly_node> heap{ arr[0] };
	for (int i{ 1 }; i < arr.size(); ++i)
		heap.add_item(arr[i]);
	for (int i{ 0 }; i < arr.size(); ++i)//go forward through array adding smallest
	{
		arr[i] = heap.root->value;
		heap.remove_item();
	}
	return arr;
}