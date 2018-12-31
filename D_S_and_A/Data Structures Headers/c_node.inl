#pragma once
#include "c_node.h"

template <class ValType>
c_node<ValType>::c_node(ValType val) : value(val), left(nullptr), right(nullptr) {}

template <class ValType>
c_node<ValType>::c_node(c_node const& other) : value{ other.value }, left{ new c_node<ValType>(other.left->value) }, right{ new c_node<ValType>(other.right->value) } {}

template <class ValType>
c_node<ValType>& c_node<ValType>::operator=(c_node const& other)
{
	if (&other == this)
		return *this;
	value{ other.value };
	left{  };
}

template <class ValType>
c_node<ValType>::~c_node()
{
	delete left, right;
	left = right = nullptr;
}
