#pragma once
#include <iterator>
#include <vector>

template <class ValType, template <class> class NodeType>
class c_bst_iterator_in_order : public std::iterator<std::forward_iterator_tag, NodeType<ValType>, size_t, NodeType<ValType> * *, NodeType<ValType> *>
{
public:
	NodeType<ValType> * * current;
	std::vector<std::pair<NodeType<ValType> *, bool>> ancestors;//I need the path to navigate back up and the boolean to tell me which way to go

	c_bst_iterator_in_order() = delete;
	explicit c_bst_iterator_in_order(NodeType<ValType> * * const& node);
	//no destructor because current is deleted in c_poly_node
	c_bst_iterator_in_order<ValType, NodeType>& operator++();
	c_bst_iterator_in_order<ValType, NodeType> operator++(int);
	bool operator==(c_bst_iterator_in_order<ValType, NodeType> other) const;
	bool operator!=(c_bst_iterator_in_order<ValType, NodeType> const& other) const;
	NodeType<ValType> * * operator*();
};

#include "c_bst_iterator_in_order.inl"