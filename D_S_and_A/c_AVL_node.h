#pragma once

template <typename  ValType>
class c_AVL_node
{
public:
	ValType value;
	c_AVL_node<ValType> * parent, * left, * right;

	c_AVL_node() = delete;

	c_AVL_node(ValType const& val) : value(val), parent(nullptr), left(nullptr), right(nullptr) {}
	c_AVL_node(ValType const& val, c_AVL_node& par) : value(val)
	{
		parent = &par;
		left = right = nullptr;
	}

	~c_AVL_node()
	{
		parent = nullptr;

		delete left;
		left = nullptr;
		delete right;
		right = nullptr;
	}
};