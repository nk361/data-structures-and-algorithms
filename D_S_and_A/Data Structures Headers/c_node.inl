#pragma once
#include "c_node.h"

template <class ValType>
c_node<ValType>::c_node(ValType val) : value(val), left(nullptr), right(nullptr) {}

template <class ValType>
c_node<ValType>::~c_node()
{
	delete left, right;
	left = right = nullptr;
}