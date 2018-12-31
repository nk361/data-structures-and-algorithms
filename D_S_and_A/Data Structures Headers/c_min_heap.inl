#pragma once
#include "c_min_heap.h"

template <class ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(ValType const& val) : c_heap<ValType, NodeType, std::less<>>(val) {}

template <class ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(std::vector<ValType> const& vals) : c_heap<ValType, NodeType, std::less<>>(vals) {}

template <class ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType, std::less<>>::add_item(val);
}

template <class ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType, std::less<>>::add_items(vals);
}

template <class ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::remove_item()
{
	c_heap<ValType, NodeType, std::less<>>::remove_item();
}