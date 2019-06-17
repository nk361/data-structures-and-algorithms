#pragma once
#include "c_red_black_poly_node.h"

template<class DataType>
c_red_black_poly_node<DataType>::c_red_black_poly_node(DataType const& val, int const& chldrn_size, bool const& r) : red(r)
{
	value = val;

	for (int i{ 0 }; i < chldrn_size; ++i)
		children.push_back(nullptr);
}

template<class DataType>
c_red_black_poly_node<DataType>::~c_red_black_poly_node()
{
	for (int i{ 0 }; i < children.size(); ++i)
	{
		delete children[i];
		children[i] = nullptr;
	}
}