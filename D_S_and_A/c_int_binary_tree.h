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

	c_node<int> * find_node(int const& val)
	{
		c_node<int> * * current = &root;
		while(true)
		{
			if((*current)->value == val)
				return *current;
			if(val < (*current)->value)
			{
				if ((*current)->left == nullptr)
					return nullptr;
				current = &((*current)->left);
			}
			else
			{
				if ((*current)->right == nullptr)
					return nullptr;
				current = &((*current)->right);
			}
		}
	}

	//find the value first ^ return it, then delete it with trickle down
	//I need a find method anyway, so might as well use it in remove

	//keep track of previous/parent node
	//find one node that has to go and remove it
	//trickle down

	//So
	//I have a left and a right child of current
	//one of current's children is the value to remove
	//So I store pointers to the left and right of that current's child
	//I check which is bigger and make that the current's new child
	//I then navigate down the subtree of that new child comparing the value of the other subtree's root
	//If I find where it belongs, I make a pointer to what's currently there to keep it
	//And then I place my subtree there and navigate down it with the other subtree
	void remove_item(int const& val) override
	{
		//c_node<int> * * remove = this->&find_node(val);
		//if(remove != nullptr)
		{
			//if(remove->left == nullptr && remove->right == nullptr)


			//c_node<int> * current = remove->left;
			//while (true)
			{
				
			}
		}

		/*c_node<int> * * current = &root;
		c_node<int> * previous = (*current);

		while(true)
		{
			
		}

		c_node<int> * * current = &root;
		while(true)
		{
			if(val < (*current)->value)
			{
				if((*current)->left->value == val)
				{
					//loop to swap values
					c_node<int> * lft = (*current)->left, * rht = (*current)->right;
					while (true)
					{
						if(lft < rht)
						{
							(*current) = (*current)->right;
							current = &((*current)->right);
							rht = 
						}
						else
						{
							
						}

					}
					break;
				}
				current = &((*current)->left);
			}
			else
			{
				if ((*current)->right->value == val)
				{
					//loop to swap values
				}
				current = &((*current)->right);
			}
		}*/
	}

	//Maybe pass the node that has the value we want to remove
	//and start the loop here for changing the tree
	void trickle_down(c_node<int> * current)
	{
		
	}
};
