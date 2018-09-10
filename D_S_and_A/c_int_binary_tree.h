#pragma once
#include "c_binary_tree.h"

class c_int_binary_tree : public c_binary_tree<int>
{
public:
	c_int_binary_tree() = delete;

	c_int_binary_tree(int const& val) : c_binary_tree<int>(val) {}

	void add_item(int const& val) override
	{
		c_node<int> * current = root;
		while (true)
		{
			if (val < current->value)
			{
				if (current->left == nullptr)
				{
					current->left = new c_node<int>{ val };
					break;
				}
				current = current->left;
			}
			else//greater than or equal to
			{
				if (current->right == nullptr)
				{
					current->right = new c_node<int>{ val };
					break;
				}
				current = current->right;
			}
		}
	}

	void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	void remove_item(int const& val) override
	{
		
	}
};
