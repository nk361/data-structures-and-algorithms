#pragma once

//Depreciated node type
template <typename  ValType>
class c_AVL_node
{
public:
	ValType value;
	c_AVL_node<ValType> * parent, * left, * right;

	c_AVL_node() = delete;
	explicit c_AVL_node(ValType const& val);
	c_AVL_node(ValType const& val, c_AVL_node * par);

	~c_AVL_node();
};

#include "c_AVL_node.inl"