#pragma once
#include <vector>

template <class ValType>
class c_poly_node
{
public:
	ValType value;
	std::vector<c_poly_node *> children;

	c_poly_node() = delete;
	explicit c_poly_node(ValType val, int const& chldrn_size);

	virtual ~c_poly_node();
};