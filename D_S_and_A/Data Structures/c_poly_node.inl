#pragma once

#include "c_poly_node.h"

template<class DataType>
c_poly_node<DataType>::c_poly_node(DataType const& val, int const& chldrn_size)
{
	value = val;

	for (int i{ 0 }; i < chldrn_size; ++i)
		children.push_back(nullptr);
}