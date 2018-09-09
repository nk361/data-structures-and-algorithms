#pragma once
#include "stdafx.h"
#include "c_node.h"
#include "c_tree.h"

class c_binary_tree : public c_tree<int>
{
public:
	c_binary_tree() = delete;

	explicit c_binary_tree(int const& num) : c_tree(num) {}
	
	void add_item(int const& val) override
	{
		c_node<int> * current = root;
		while(true)
		{
			if(val < current->value)// && current.left == nullptr)
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
				if(current->right == nullptr)
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

	void remove_item(int const& val)
	{
		
	}
};
