#pragma once
#include <iterator>

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_linked_list_iterator : public std::iterator<std::forward_iterator_tag, NodeType, size_t, NodeType * *, NodeType *>
{
	NodeType * * current;
public:
	c_linked_list_iterator() = delete;
	explicit c_linked_list_iterator(NodeType * * const& node);
	//no destructor because current is deleted in c_poly_node
	c_linked_list_iterator<DataType, NodeType>& operator++();
	c_linked_list_iterator<DataType, NodeType> operator++(int);
	bool operator==(c_linked_list_iterator<DataType, NodeType> other) const;
	bool operator!=(c_linked_list_iterator<DataType, NodeType> const& other) const;
	NodeType * * operator*();
};

#include "c_linked_list_iterator.inl"