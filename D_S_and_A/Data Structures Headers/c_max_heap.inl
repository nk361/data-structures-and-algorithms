#pragma once
#include "c_max_heap.h"

template <class ValType, template<class> class NodeType>
c_max_heap<ValType, NodeType>::c_max_heap(ValType const& val) : c_heap<ValType, NodeType, std::greater<>>(val) {}

template <class ValType, template<class> class NodeType>
c_max_heap<ValType, NodeType>::c_max_heap(std::vector<ValType> const& vals) : c_heap<ValType, NodeType, std::greater<>>(vals) {}

template <class ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType, std::greater<>>::add_item(val);
}

template <class ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType, std::greater<>>::add_items(vals);
}

template <class ValType, template<class> class NodeType>
void c_max_heap<ValType, NodeType>::remove_item()
{
	c_heap<ValType, NodeType, std::greater<>>::remove_item();
}