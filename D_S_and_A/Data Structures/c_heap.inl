#pragma once

#include <vector>

#include "c_heap.h"

template<class DataType, class NodeType, typename Operation>
c_heap<DataType, NodeType, Operation>::c_heap(DataType const& val) : c_binary_tree<DataType, NodeType>(val), size(1) {}

//sends the first item off as root in binary tree, adds the rest
template<class DataType, class NodeType, typename Operation>
c_heap<DataType, NodeType, Operation>::c_heap(std::vector<DataType> const& vals) : c_binary_tree<DataType, NodeType>(vals[0]), size(1)
{
	for (size_t i{ 1 }; i < vals.size(); ++i)
		c_heap<DataType, NodeType, Operation>::add_item(vals[i]);
}

template<class DataType, class NodeType, typename Operation>
void c_heap<DataType, NodeType, Operation>::trickle_up(std::vector<NodeType * *> ancstrs) const
{
	Operation const op = Operation();
	for (int i{ static_cast<int>(ancstrs.size()) - 1 }; i >= 1; --i)//go up the ancestors list stopping at ancestor 1 not last
		if (op((*ancstrs[i])->value, (*ancstrs[i - 1])->value))//check if current item is greater/less than it's parent
			std::swap((*ancstrs[i])->value, (*ancstrs[i - 1])->value);
		else
			break;//break because no nodes above should be less/greater than their children if added correctly
}

template<class DataType, class NodeType, typename Operation>
void c_heap<DataType, NodeType, Operation>::trickle_down()
{
	Operation const op = Operation();
	if (c_heap<DataType, NodeType, Operation>::root->children[0] != nullptr)//if root has at least one child that may need swapped
	{
		NodeType * * current{ &(c_heap<DataType, NodeType, Operation>::root) };
		while (true)
		{
			if ((*current)->children[0] == nullptr && (*current)->children[1] == nullptr)//reached leaf node
				break;
			if ((*current)->children[1] == nullptr)//no right, swap left (heaps can never have no left child while having a right child, no check needed)
			{
				if (op((*current)->children[0]->value, (*current)->value))
				{
					std::swap((*current)->value, ((*current)->children[0])->value);
					break;//in a heap, the child, of a parent with one node, must be a leaf node
				}
				break;
			}

			if (op((*current)->children[0]->value, (*current)->value) || op((*current)->children[1]->value, (*current)->value))//at least one of the children is greater/less
				if (op((*current)->children[0]->value, (*current)->children[1]->value))//left is the greatest of children
				{
					std::swap((*current)->value, (*current)->children[0]->value);
					current = &(*current)->children[0];
				}
				else//right is the greatest of children
				{
					std::swap((*current)->value, (*current)->children[1]->value);
					current = &(*current)->children[1];
				}
			else//if the node has two children and neither of their values are greater/less
				break;
		}
	}
}

template <class DataType, class NodeType, typename Operation>
DataType c_heap<DataType, NodeType, Operation>::get_top()
{
	return c_heap<DataType, NodeType, Operation>::root->value;
}

template<class DataType, class NodeType, typename Operation>
void c_heap<DataType, NodeType, Operation>::add_item(DataType const& val)//virtual goes only in class declaration
{
	int const open_spot{ 1 + amount_last_level(size) };//know the destination, find how many are in the last level + 1
	int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direction to head

	NodeType * * current{ &(c_heap<DataType, NodeType, Operation>::root) };
	std::vector<NodeType * *> ancestors{ current };//for navigation up to root, after adding an item, in trickle_up

	for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
		if (open_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
			if ((*current)->children[0] != nullptr)//go left
			{
				current = &(*current)->children[0];
				ancestors.push_back(current);
			}
			else
			{
				(*current)->children[0] = new NodeType{ val, 2 };
				ancestors.push_back(&(*current)->children[0]);//add the newest node to ancestors
				trickle_up(ancestors);//trickle up moving the new value up as high as it needs to go
				++size;
				break;
			}
		else//if the goal is rightward
		{
			previous_calc += max_of_last_level / amount_in_level(current_level + 1);//to be sure to decide where to go based on right half

			if ((*current)->children[1] != nullptr)//go right
			{
				current = &(*current)->children[1];
				ancestors.push_back(current);
			}
			else
			{
				(*current)->children[1] = new NodeType{ val, 2 };
				ancestors.push_back(&(*current)->children[1]);//add the newest node to ancestors
				trickle_up(ancestors);//trickle up moving the new value up as high as it needs to go
				++size;
				break;
			}
		}
}

template<class DataType, class NodeType, typename Operation>
void c_heap<DataType, NodeType, Operation>::add_items(std::vector<DataType> const& vals)
{
	for (DataType val : vals)
		c_heap<DataType, NodeType, Operation>::add_item(val);
}

//in a heap, always remove only the root
template<class DataType, class NodeType, typename Operation>
void c_heap<DataType, NodeType, Operation>::remove_item()
{
	int last_spot;
	if (amount_full_tree(amount_complete_levels(size)) == size)//if this is a full tree, last spot in last level
		last_spot = amount_in_level(amount_complete_levels(size));
	else//otherwise, go onto last node in level
		last_spot = amount_last_level(size);

	int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direcion to head

	NodeType * * current{ &(c_heap<DataType, NodeType, Operation>::root) };//to navigate, pointer to pointer to assign nullptr and delete correctly

	for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
		if (last_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
			if ((*current)->children[0] != nullptr)//go left
				current = &(*current)->children[0];
			else
			{
				std::swap(c_heap<DataType, NodeType, Operation>::root->value, (*current)->value);//swap last item's and root's value only
				delete *current;
				*current = nullptr;
				if (c_heap<DataType, NodeType, Operation>::root != nullptr)//no need to call if no root
					trickle_down();
				--size;
				break;
			}
		else//if the goal is rightward
		{
			previous_calc += max_of_last_level / amount_in_level(current_level + 1);//to be sure to decide where to go based on right half

			if ((*current)->children[1] != nullptr)//go right
				current = &(*current)->children[1];
			else
			{
				std::swap(c_heap<DataType, NodeType, Operation>::root->value, (*current)->value);//swap last item's and root's value only
				delete *current;
				*current = nullptr;
				if (c_heap<DataType, NodeType, Operation>::root != nullptr)//no need to call if no root
					trickle_down();
				--size;
				break;
			}
		}
}

//takes a level and returns how many nodes could be side by side in it
template<class DataType, class NodeType, typename Operation>
int c_heap<DataType, NodeType, Operation>::amount_in_level(int const& level)//static also only appears in class only
{
	return static_cast<int>(pow(2, level));
}

//takes an amount of levels and returns the amount of nodes that could fit into a tree of that size
template<class DataType, class NodeType, typename Operation>
int c_heap<DataType, NodeType, Operation>::amount_full_tree(int const& levels)//reduced by one because four levels includes level 0
{
	return static_cast<int>(pow(2, levels)) - 1;
}

//takes a size/amount of nodes in a tree and returns how many levels are full/complete in the tree
template<class DataType, class NodeType, typename Operation>
int c_heap<DataType, NodeType, Operation>::amount_complete_levels(int const& sz)
{
	int temp{ sz };
	for (int level{ 0 }; true; ++level)
	{
		if (temp - amount_in_level(level) < 0)
			return level;
		if (temp - amount_in_level(level) == 0)
			return  level + 1;
		temp -= amount_in_level(level);
	}
}

//takes a size and returns how many nodes are in the last level of the tree including zero if the tree is complete
template<class DataType, class NodeType, typename Operation>
int c_heap<DataType, NodeType, Operation>::amount_last_level(int const& sz)
{
	if (sz == 0)//when root is the last level, return 1 instead of 0
		return 1;
	return sz - amount_full_tree(amount_complete_levels(sz));
}