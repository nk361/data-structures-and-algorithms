#pragma once
#include "c_node.h"

template <typename  ValType>
class c_AVL_node : public c_node<ValType>
{
public:
	c_AVL_node<ValType> * parent;

	c_AVL_node() = delete;
	c_AVL_node(ValType const& val) : c_node(val), parent(nullptr) {}
	c_AVL_node(ValType const& val, c_node<ValType> const& par) : c_node(val), parent(par) {}

	~c_AVL_node()
	{
		delete parent;
		parent = nullptr;
	}
};