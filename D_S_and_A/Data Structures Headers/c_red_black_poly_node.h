#pragma once
#include <vector>

template <class ValType>
class c_red_black_poly_node
{
public:
	ValType value;
	std::vector<c_red_black_poly_node *> children;
	bool red;//false if black

	c_red_black_poly_node() = delete;
	explicit c_red_black_poly_node(ValType const& val, int const& chldrn_size, bool const& r = true);

	~c_red_black_poly_node();
};

#include "c_red_black_poly_node.inl"