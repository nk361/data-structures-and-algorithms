#pragma once
#include "c_max_heap.h"

template<class DataType, class NodeType>
c_max_heap<DataType, NodeType>::c_max_heap(DataType const& val) : c_heap<DataType, NodeType, std::greater<>>(val) {}

template<class DataType, class NodeType>
c_max_heap<DataType, NodeType>::c_max_heap(std::vector<DataType> const& vals) : c_heap<DataType, NodeType, std::greater<>>(vals) {}

template<class DataType, class NodeType>
void c_max_heap<DataType, NodeType>::add_item(DataType const& val)
{
	c_heap<DataType, NodeType, std::greater<>>::add_item(val);
}

template<class DataType, class NodeType>
void c_max_heap<DataType, NodeType>::add_items(std::vector<DataType> const& vals)
{
	c_heap<DataType, NodeType, std::greater<>>::add_items(vals);
}

template<class DataType, class NodeType>
void c_max_heap<DataType, NodeType>::remove_item()
{
	c_heap<DataType, NodeType, std::greater<>>::remove_item();
}