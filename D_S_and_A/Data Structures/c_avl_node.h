#pragma once

//Depreciated node type
template <class ValType>
class c_avl_node
{
public:
	ValType value;
	c_avl_node<ValType> * parent, * left, * right;

	c_avl_node() = delete;
	explicit c_avl_node(ValType const& val);
	c_avl_node(ValType const& val, c_avl_node * par);

	~c_avl_node();
};

#include "c_avl_node.inl"