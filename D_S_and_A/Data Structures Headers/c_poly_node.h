#pragma once
#include <vector>

template <class ValType>
class c_poly_node
{
public:
	ValType value;
	std::vector<c_poly_node *> children;

	c_poly_node() = delete;
	explicit c_poly_node(ValType const& val, int const& chldrn_size);
	c_poly_node(c_poly_node const& other)
	{
		value = other.value;
		for (c_poly_node * child : other.children)
			children.push_back(nullptr);
	}

	virtual ~c_poly_node();

	c_poly_node<ValType>& operator=(c_poly_node const& other)
	{
		value = other.value;
		children = other.children;
		return *this;
	}
};

#include "c_poly_node.inl"