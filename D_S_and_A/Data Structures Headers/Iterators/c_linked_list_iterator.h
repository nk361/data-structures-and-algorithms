#pragma once
#include <iterator>

template <class ValType, template<class> class NodeType>
class c_linked_list_iterator : public std::iterator<std::forward_iterator_tag, NodeType<ValType>, size_t, NodeType<ValType> * *, NodeType<ValType> *>
{
	NodeType<ValType> * * current;
public:
	c_linked_list_iterator() = delete;
	explicit c_linked_list_iterator(NodeType<ValType> * * const& node);
	//no destructor because current is deleted in c_poly_node
	c_linked_list_iterator<ValType, NodeType>& operator++();
	c_linked_list_iterator<ValType, NodeType> operator++(int);
	bool operator==(c_linked_list_iterator<ValType, NodeType> other) const;
	bool operator!=(c_linked_list_iterator<ValType, NodeType> const& other) const;
	NodeType<ValType> * * operator*();
};

#include "c_linked_list_iterator.inl"