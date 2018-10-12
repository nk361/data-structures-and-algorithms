#pragma once
#include "c_heap.h"

class c_max_heap : public c_heap<int>
{
public:
	c_max_heap() = delete;

	explicit c_max_heap(int const& val) : c_heap(val) {}

	explicit c_max_heap(std::vector<int> const& vals) : c_heap(vals[0])
	{
		for (size_t i{ 1 }; i < vals.size(); ++i)//start at one, send first val off to be root
			this->c_max_heap::add_item(vals[i]);
	}

	void trickle_up(std::vector<c_node<int> * *> ancstrs) const
	{
		for (int i{ static_cast<int>(ancstrs.size()) - 1 }; i >= 1; --i)//go up the ancestors list stopping at ancestor 1 not last
			if ((*ancstrs[i])->value > (*ancstrs[i - 1])->value)//check if current item is greater than it's parent
				std::swap((*ancstrs[i])->value, (*ancstrs[i - 1])->value);
			else
				break;//break because no nodes above should be less than their children if added correctly
	}

	void trickle_down()
	{
		if(root->left != nullptr)//if root has at least one child that may need swapped
		{
			c_node<int> * * current{ &root };
			while(true)
			{
				if ((*current)->left == nullptr && (*current)->right == nullptr)//reached leaf node
					break;
				if((*current)->right == nullptr)//no right, swap left (heaps can never have a no left child while having a right child, no check needed)
				{
					if ((*current)->value < (*current)->left->value)
					{
						std::swap((*current)->value, ((*current)->left)->value);
						break;//in a heap, the child, of a parent with one node, must be a leaf node
					}
					break;
				}
				
				if ((*current)->value < (*current)->left->value || (*current)->value < (*current)->right->value)//at least one of the children is greater
				{
					if((*current)->left->value > (*current)->right->value)//left is the greatest of children
					{
						std::swap((*current)->value, (*current)->left->value);
						current = &(*current)->left;
					}
					else//right is the greatest of children
					{
						std::swap((*current)->value, (*current)->right->value);
						current = &(*current)->right;
					}
				}
				else//if the node has two children and neither of their values are greater
					break;
			}
		}
	}

	void add_item(int const& val) override
	{
		int const open_spot{ 1 + amount_last_level(size) };//know the destination, find how many are in the last level + 1
		int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direcion to head

		c_node<int> * * current{ &root };
		std::vector<c_node<int> * *> ancestors{ current };//for navigation up to root, after adding an item, in trickle_up

		for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
			if(open_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
				if((*current)->left != nullptr)//go left
				{
					current = &(*current)->left;
					ancestors.push_back(current);
				}
				else
				{
					(*current)->left = new c_node<int>{ val };
					ancestors.push_back(&(*current)->left);//add the newest node to ancestors
					trickle_up(ancestors);//trickle up moving the new value up as high as it needs to go
					++size;
					break;
				}
			else//if the goal is rightward
			{
				previous_calc += max_of_last_level / amount_in_level(current_level + 1);//to be sure to decide where to go based on right half

				if((*current)->right != nullptr)//go right
				{
					current = &(*current)->right;
					ancestors.push_back(current);
				}
				else
				{
					(*current)->right = new c_node<int>{ val };
					ancestors.push_back(&(*current)->right);//add the newest node to ancestors
					trickle_up(ancestors);//trickle up moving the new value up as high as it needs to go
					++size;
					break;
				}
			}
	}

	void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	void remove_item() override//this would be the same except the > check in a min heap
	{
		int last_spot;
		if (amount_full_tree(amount_complete_levels(size)) == size)//if this is a full tree, last spot in last level
			last_spot = amount_in_level(amount_complete_levels(size));
		else//otherwise, go onto last node in level
			last_spot = amount_last_level(size);
		
		int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direcion to head

		c_node<int> * * current{ &root };//to navigate, pointer to pointer to assign nullptr and delete correctly
		
		for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
			if (last_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
				if ((*current)->left != nullptr)//go left
					current = &(*current)->left;
				else
				{
					std::swap(root->value, (*current)->value);//swap last item's and root's value only
					delete *current;
					*current = nullptr;
					if(root != nullptr)//no need to call if no root
						trickle_down();
					--size;
					break;
				}
			else//if the goal is rightward
			{
				previous_calc += max_of_last_level / amount_in_level(current_level + 1);//to be sure to decide where to go based on right half

				if ((*current)->right != nullptr)//go right
					current = &(*current)->right;
				else
				{
					std::swap(root->value, (*current)->value);//swap last item's and root's value only
					delete *current;
					*current = nullptr;
					if (root != nullptr)//no need to call if no root
						trickle_down();
					--size;
					break;
				}
			}
	}
};