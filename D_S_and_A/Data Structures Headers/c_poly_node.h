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

	virtual ~c_poly_node();

	c_poly_node<ValType>& operator=(c_poly_node const& other)
	{
		value = other.value;
		children = other.children;
		return *this;
	}

	//bool operator==(c_poly_node other) { return true; }

	/*bool operator==(c_poly_node other) { return value == other.value && children == other.children; }
	bool operator!=(c_poly_node other) { return !(*this == other); }*/
};

#include "c_poly_node.inl"