#pragma once

#include <vector>

template<class DataType>
class c_red_black_poly_node
{
public:
	DataType value;
	std::vector<c_red_black_poly_node *> children;
	bool red;//false if black

	c_red_black_poly_node() = delete;
	explicit c_red_black_poly_node(DataType const& val, int const& chldrn_size, bool const& r = true);

	~c_red_black_poly_node();
};

#include "c_red_black_poly_node.inl"