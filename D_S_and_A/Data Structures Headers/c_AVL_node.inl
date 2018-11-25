#pragma once
#include "c_avl_node.h"

template <typename  ValType>
c_avl_node<ValType>::c_avl_node(ValType const& val) : value(val), parent(nullptr), left(nullptr), right(nullptr) {}

template <typename  ValType>
c_avl_node<ValType>::c_avl_node(ValType const& val, c_avl_node * par) : value(val), parent(par), left(nullptr), right(nullptr) {}

template <typename  ValType>
c_avl_node<ValType>::~c_avl_node()
{
	parent = nullptr;

	delete left;
	left = nullptr;
	delete right;
	right = nullptr;
}