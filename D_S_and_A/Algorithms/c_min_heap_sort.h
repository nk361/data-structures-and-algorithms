#pragma once
#include "../Data Structures/c_min_heap.h"

template<class MyType>
class c_min_heap_sort
{
public:
	MyType static *sort(MyType arr[], int const& size)
	{
		c_min_heap<MyType> heap{ arr[0] };
		for (int i = 1; i < size; ++i)
			heap.add_item(arr[i]);
		for (int i = 0; i < size; ++i)//go forward through array adding smallest
		{
			arr[i] = heap.root->value;
			heap.remove_item();
		}
		return arr;
	}
};