#pragma once
#include "c_binary_tree.h"

class c_int_binary_tree : public c_binary_tree<int>
{
public:
	c_int_binary_tree() = delete;

	c_int_binary_tree(int const& val) : c_binary_tree<int>(val) {}

	c_int_binary_tree(std::vector<int> const& vals) : c_binary_tree<int>(vals[0])
	{
		for (size_t i = 1; i < vals.size(); ++i)
			this->c_int_binary_tree::add_item(vals[i]);
	}

	void add_item(int const& val) override
	{
		c_node<int> * current = root;
		while (true)
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

	void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	c_node<int> * * find_node(int const& val)
	{
		c_node<int> * * current = &root;
		while(true)
		{
			if((*current)->value == val)
				return current;
			if(val < (*current)->value)
			{
				if ((*current)->left == nullptr)
					return &(*current)->left;//returning a reference to a pointer holding nullptr
				current = &(*current)->left;
			}
			else
			{
				if ((*current)->right == nullptr)
					return &(*current)->right;//returning a reference to a pointer holding nullptr
				current = &(*current)->right;
			}
		}
	}

	void remove_item(int const& val) override
	{
		c_node<int> * * found = find_node(val);
		
		if((*found) != nullptr)
			if((*found)->left == nullptr && (*found)->right == nullptr)
			{
				delete (*found);
				(*found) = nullptr;
			}
			else if((*found)->right == nullptr)
				(*found) = (*found)->left;
			else if((*found)->left == nullptr)
				(*found) = (*found)->right;
			else//both child nodes have values
			{
				c_node<int> * * current = &(*found)->right;
				while(true)//search for the leftmost node of right child
					if ((*current)->left != nullptr)
						current = &(*current)->left;
					else
						break;
				(*found)->value = (*current)->value;

				if((*current)->right == nullptr)//delete node if all the way left
				{
					delete (*current);
					(*current) = nullptr;
				}
				else//move right nodes up if it was purely the right node
					(*current) = (*current)->right;
			}
	}

	//Maybe pass the node that has the value we want to remove
	//and start the loop here for changing the tree
	void trickle_down(c_node<int> * current)
	{
		
	}
};
