#pragma once
#include "c_AVL_node.h"
#include "c_AVL_binary_tree.h"

class c_AVL_int_binary_tree : public c_AVL_binary_tree<int, c_AVL_node>
{
public:
	c_AVL_int_binary_tree() = delete;

	explicit c_AVL_int_binary_tree(int const& val) : c_AVL_binary_tree(val) {}//calling this leads to c_node...

	explicit c_AVL_int_binary_tree(std::vector<int> const& vals) : c_AVL_binary_tree(vals[0])
	{
		for (size_t i = 1; i < vals.size(); ++i)//because parent isn't being set for the avl nodes?
			this->c_AVL_int_binary_tree::add_item(vals[i]);
	}

	void check_balance(c_AVL_node<int> const& new_node)
	{
		
	}

	virtual void add_item(int const& val) override
	{
		//I need to add an item, know where it was, check for violations, and fix them if there are any
		c_AVL_node<int> * * current = &root;
		c_AVL_node<int> * * previous = current;
		while (true)
		{
			if (val < (*current)->value)
			{
				if ((*current)->left == nullptr)
				{
					(*current)->left = new c_AVL_node<int>{ val, **previous };
					check_balance(*(*current)->left);
					break;
				}
				previous = current;
				current = &(*current)->left;
			}
			else//greater than or equal to
			{
				if ((*current)->right == nullptr)
				{
					(*current)->right = new c_AVL_node<int>{ val, **previous };
					check_balance(*(*current)->right);
					break;
				}
				previous = current;
				current = &(*current)->right;
			}
		}
	}

	virtual void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	virtual void remove_item(int const& val) override
	{
		
	}
};
