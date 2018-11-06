#pragma once
#include "c_max_heap.h"

template <typename ValType, template<class> class NodeType>
c_max_heap<ValType, NodeType>::c_max_heap(ValType const& val) : c_heap<ValType, NodeType>(val) {}

template <typename ValType, template<class> class NodeType>
c_max_heap<ValType, NodeType>::c_max_heap(std::vector<ValType> const& vals, bool(*greater_than)(ValType const&, ValType const&)) : c_heap<ValType, NodeType>(vals, greater_than) {}

template <typename ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType>::add_item(val, greater_than);
}

template <typename ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType>::add_items(vals, greater_than);
}

template <typename ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::remove_item()
{
	c_heap<ValType, NodeType>::remove_item(greater_than);
}