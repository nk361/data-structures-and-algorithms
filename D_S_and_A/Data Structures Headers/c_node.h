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
	c_node(c_node const& other);
	c_node& operator=(c_node const& other);

	virtual ~c_node();
};

#include "c_node.inl"