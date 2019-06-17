#pragma once
#include <iterator>
#include <vector>

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_bst_iterator_in_order : public std::iterator<std::forward_iterator_tag, NodeType, size_t, NodeType * *, NodeType *>
{
public:
	NodeType * * current;
	std::vector<std::pair<NodeType *, bool>> ancestors;//I need the path to navigate back up and the boolean to tell me which way to go

	c_bst_iterator_in_order() = delete;
	explicit c_bst_iterator_in_order(NodeType * * const& node);
	//no destructor because current is deleted in c_poly_node
	c_bst_iterator_in_order<DataType, NodeType>& operator++();
	c_bst_iterator_in_order<DataType, NodeType> operator++(int);
	bool operator==(c_bst_iterator_in_order<DataType, NodeType> other) const;
	bool operator!=(c_bst_iterator_in_order<DataType, NodeType> const& other) const;
	NodeType * * operator*();
};

#include "c_bst_iterator_in_order.inl"