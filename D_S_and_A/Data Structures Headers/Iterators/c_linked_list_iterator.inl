#pragma once
#include "c_linked_list_iterator.h"

template <class ValType, template<class> class NodeType>
c_linked_list_iterator<ValType, NodeType>::c_linked_list_iterator(NodeType<ValType> * * const& node) : current(node) {}

template <class ValType, template<class> class NodeType>
c_linked_list_iterator<ValType, NodeType>& c_linked_list_iterator<ValType, NodeType>::operator++()
{
	current = &(*current)->children[0]; return *this;
}

template <class ValType, template<class> class NodeType>
c_linked_list_iterator<ValType, NodeType> c_linked_list_iterator<ValType, NodeType>::operator++(int)//postfix
{
	c_linked_list_iterator<ValType, NodeType> temp = *this; ++*this; return temp;
}

template <class ValType, template<class> class NodeType>
bool c_linked_list_iterator<ValType, NodeType>::operator==(c_linked_list_iterator<ValType, NodeType> other) const//check if the node they point to is the same
{
	return *current == **other;
}

template <class ValType, template<class> class NodeType>
bool c_linked_list_iterator<ValType, NodeType>::operator!=(c_linked_list_iterator<ValType, NodeType> const& other) const
{
	return !(*this == other);
}

template <class ValType, template<class> class NodeType>
NodeType<ValType> * * c_linked_list_iterator<ValType, NodeType>::operator*()
{
	return current;
}