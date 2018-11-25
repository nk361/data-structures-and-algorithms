#pragma once
#include "c_poly_node.h"

template <typename ValType>
class c_red_black_tree_node : public c_poly_node<ValType>
{
public:
	bool red;//false if black

	c_red_black_tree_node() = delete;
	explicit c_red_black_tree_node(ValType const& val, bool const& r = true);

	~c_red_black_tree_node() = default;//no code, just call c_poly_node's virtual destructor
};

#include "c_red_black_tree_node.inl"