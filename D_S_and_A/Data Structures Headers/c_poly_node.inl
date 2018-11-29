#pragma once
#include "c_poly_node.h"

template <class ValType>
c_poly_node<ValType>::c_poly_node(ValType const& val, int const& chldrn_size)
{
	value = val;

	for (int i{ 0 }; i < chldrn_size; ++i)
		children.push_back(nullptr);
}

template <class ValType>
c_poly_node<ValType>::~c_poly_node()
{
	for (int i{ 0 }; i < children.size(); ++i)
	{
		delete children[i];
		children[i] = nullptr;
	}
}