#pragma once
#include "c_min_heap.h"

template <typename ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(ValType const& val) : c_heap<ValType, NodeType>(val) {}

template <typename ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(std::vector<ValType> const& vals, bool(*less_than)(ValType const&, ValType const&)) : c_heap<ValType, NodeType>(vals, less_than) {}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType>::add_item(val, less_than);
}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType>::add_items(vals, less_than);
}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::remove_item()
{
	c_heap<ValType, NodeType>::remove_item(less_than);
}