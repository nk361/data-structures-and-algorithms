#pragma once

#include <vector>

#include "c_priority_queue.h"

template <class DataType, class HeapType>
c_priority_queue<DataType, HeapType>::c_priority_queue(DataType const& val) : heap(val) {}

template <class DataType, class HeapType>
c_priority_queue<DataType, HeapType>::c_priority_queue(std::vector<DataType> const& vals) : heap(vals) {}

template <class DataType, class HeapType>
DataType c_priority_queue<DataType, HeapType>::get_top()
{
	return heap.get_top();
}

template <class  DataType, class HeapType>
void c_priority_queue<DataType, HeapType>::add_item(DataType const& val)
{
	heap.add_item(val);
}

template <class  DataType, class HeapType>
void c_priority_queue<DataType, HeapType>::add_items(std::vector<DataType> const& vals)
{
	heap.add_items(vals);
}

template <class  DataType, class HeapType>
void c_priority_queue<DataType, HeapType>::remove_item()
{
	heap.remove_item();
}