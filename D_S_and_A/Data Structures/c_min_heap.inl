#pragma once

#include <vector>

#include "c_min_heap.h"

template<class DataType, class NodeType>
c_min_heap<DataType, NodeType>::c_min_heap(DataType const& val) : c_heap<DataType, NodeType, std::less<>>(val) {}

template<class DataType, class NodeType>
c_min_heap<DataType, NodeType>::c_min_heap(std::vector<DataType> const& vals) : c_heap<DataType, NodeType, std::less<>>(vals) {}

template<class DataType, class NodeType>
void c_min_heap<DataType, NodeType>::add_item(DataType const& val)
{
	c_heap<DataType, NodeType, std::less<>>::add_item(val);
}

template<class DataType, class NodeType>
void c_min_heap<DataType, NodeType>::add_items(std::vector<DataType> const& vals)
{
	c_heap<DataType, NodeType, std::less<>>::add_items(vals);
}

template<class DataType, class NodeType>
void c_min_heap<DataType, NodeType>::remove_item()
{
	c_heap<DataType, NodeType, std::less<>>::remove_item();
}