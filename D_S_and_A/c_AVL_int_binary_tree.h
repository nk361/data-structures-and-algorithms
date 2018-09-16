#pragma once
#include "c_int_binary_tree.h"
#include "c_AVL_node.h"

class c_AVL_int_binary_tree : public c_int_binary_tree<c_AVL_node>
{
public:
	c_AVL_int_binary_tree() = delete;

	explicit c_AVL_int_binary_tree(int const& val) : c_int_binary_tree(val) {}

	void add_item(int const& val) override
	{
		//I need to add an item, know where it was, check for violations, and fix them if there are any
	}

	void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}
};
