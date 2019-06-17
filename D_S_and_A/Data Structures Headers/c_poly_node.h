#pragma once
#include <vector>

template<class DataType>
class c_poly_node
{
public:
	DataType value;
	std::vector<c_poly_node *> children;

	c_poly_node() = delete;
	explicit c_poly_node(DataType const& val, int const& chldrn_size);
};

#include "c_poly_node.inl"