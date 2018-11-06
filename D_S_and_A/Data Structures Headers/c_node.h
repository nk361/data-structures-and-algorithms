#pragma once
//Depreciated node type
template <class ValType>
class c_node
{
public:
	ValType value;
	c_node * left, * right;

	c_node() = delete;
	explicit c_node(ValType val);

	virtual ~c_node();
};

#include "c_node.inl"