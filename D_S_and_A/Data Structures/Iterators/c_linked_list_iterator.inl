#pragma once
#include "c_linked_list_iterator.h"

template<class DataType, class NodeType>
c_linked_list_iterator<DataType, NodeType>::c_linked_list_iterator(NodeType * * const& node) : current(node) {}

template<class DataType, class NodeType>
c_linked_list_iterator<DataType, NodeType>& c_linked_list_iterator<DataType, NodeType>::operator++()
{
	current = &(*current)->children[0]; return *this;
}

template<class DataType, class NodeType>
c_linked_list_iterator<DataType, NodeType> c_linked_list_iterator<DataType, NodeType>::operator++(int)//postfix
{
	c_linked_list_iterator<DataType, NodeType> temp = *this; ++*this; return temp;
}

template<class DataType, class NodeType>
bool c_linked_list_iterator<DataType, NodeType>::operator==(c_linked_list_iterator<DataType, NodeType> other) const//check if the node they point to is the same
{
	return *current == **other;
}

template<class DataType, class NodeType>
bool c_linked_list_iterator<DataType, NodeType>::operator!=(c_linked_list_iterator<DataType, NodeType> const& other) const
{
	return !(*this == other);
}

template<class DataType, class NodeType>
NodeType * * c_linked_list_iterator<DataType, NodeType>::operator*()
{
	return current;
}