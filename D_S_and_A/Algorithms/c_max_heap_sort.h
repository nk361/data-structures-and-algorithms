#pragma once
#include "../Data Structures/c_max_heap.h"

template<class MyType>
class c_max_heap_sort
{
public:
	MyType static *sort(MyType arr[], int const& size)
	{
		c_max_heap<MyType> heap{ arr[0] };
		for (int i = 1; i < size; ++i)
			heap.add_item(arr[i]);
		for (int i = size - 1; i >= 0; --i)//go backward through array adding largest
		{
			arr[i] = heap.root->value;
			heap.remove_item();
		}
		return arr;
	}
};