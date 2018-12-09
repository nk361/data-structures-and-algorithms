#pragma once
#include "c_max_heap.h"

template <class ValType, template<class> class NodeType, typename Operation>
c_max_heap<ValType, NodeType, Operation>::c_max_heap(ValType const& val) : c_heap<ValType, NodeType, Operation>(val) {}

template <class ValType, template<class> class NodeType, typename Operation>
c_max_heap<ValType, NodeType, Operation>::c_max_heap(std::vector<ValType> const& vals) : c_heap<ValType, NodeType, Operation>(vals) {}

template <class ValType, template<class> class NodeType, typename Operation>
void c_max_heap<ValType, NodeType, Operation>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType, Operation>::add_item(val);
}

template <class ValType, template<class> class NodeType, typename Operation>
void c_max_heap<ValType, NodeType, Operation>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType, Operation>::add_items(vals);
}

template <class ValType, template<class> class NodeType, typename Operation>
void c_max_heap<ValType, NodeType, Operation>::remove_item()
{
	c_heap<ValType, NodeType, Operation>::remove_item();
}