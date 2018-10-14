#pragma once
#include <cmath>
#include "c_node.h"
#include "c_binary_tree.h"

//in a heap, always remove only the root
template <typename  ValType>
class c_heap : public c_binary_tree<ValType, c_node>
{
public:
	int size;

	c_heap() = delete;

	explicit c_heap(ValType const& val) : c_binary_tree<ValType, c_node>(val), size(1) {}

	//sends the first item off as root in binary tree, adds the rest
	explicit c_heap(std::vector<ValType> const& vals, bool (*op)(ValType const& left, ValType const& right)) : c_binary_tree<ValType, c_node>(vals[0]), size(1)
	{
		for (size_t i{ 1 }; i < vals.size(); ++i)
			c_heap::add_item(vals[i], (*op));
	}

	void trickle_up(std::vector<c_node<ValType> * *> ancstrs, bool(*op)(ValType const& left, ValType const& right)) const
	{
		for (int i{ static_cast<int>(ancstrs.size()) - 1 }; i >= 1; --i)//go up the ancestors list stopping at ancestor 1 not last
			if (op((*ancstrs[i])->value, (*ancstrs[i - 1])->value))//check if current item is greater/less than it's parent
				std::swap((*ancstrs[i])->value, (*ancstrs[i - 1])->value);
			else
				break;//break because no nodes above should be less/greater than their children if added correctly
	}

	void trickle_down(bool(*op)(ValType const& left, ValType const& right))
	{
		if (root->left != nullptr)//if root has at least one child that may need swapped
		{
			c_node<ValType> * * current{ &root };
			while (true)
			{
				if ((*current)->left == nullptr && (*current)->right == nullptr)//reached leaf node
					break;
				if ((*current)->right == nullptr)//no right, swap left (heaps can never have a no left child while having a right child, no check needed)
				{
					if (op((*current)->left->value, (*current)->value))
					{
						std::swap((*current)->value, ((*current)->left)->value);
						break;//in a heap, the child, of a parent with one node, must be a leaf node
					}
					break;
				}

				if (op((*current)->left->value, (*current)->value) || op((*current)->right->value, (*current)->value))//at least one of the children is greater/less
					if (op((*current)->left->value, (*current)->right->value))//left is the greatest of children
					{
						std::swap((*current)->value, (*current)->left->value);
						current = &(*current)->left;
					}
					else//right is the greatest of children
					{
						std::swap((*current)->value, (*current)->right->value);
						current = &(*current)->right;
					}
				else//if the node has two children and neither of their values are greater/less
					break;
			}
		}
	}

	virtual void add_item(ValType const& val, bool (*op)(ValType const& left, ValType const& right))
	{
		int const open_spot{ 1 + amount_last_level(size) };//know the destination, find how many are in the last level + 1
		int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direcion to head

		c_node<ValType> * * current{ &root };
		std::vector<c_node<ValType> * *> ancestors{ current };//for navigation up to root, after adding an item, in trickle_up

		for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
			if (open_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
				if ((*current)->left != nullptr)//go left
				{
					current = &(*current)->left;
					ancestors.push_back(current);
				}
				else
				{
					(*current)->left = new c_node<ValType>{ val };
					ancestors.push_back(&(*current)->left);//add the newest node to ancestors
					trickle_up(ancestors, (*op));//trickle up moving the new value up as high as it needs to go
					++size;
					break;
				}
			else//if the goal is rightward
			{
				previous_calc += max_of_last_level / amount_in_level(current_level + 1);//to be sure to decide where to go based on right half

				if ((*current)->right != nullptr)//go right
				{
					current = &(*current)->right;
					ancestors.push_back(current);
				}
				else
				{
					(*current)->right = new c_node<ValType>{ val };
					ancestors.push_back(&(*current)->right);//add the newest node to ancestors
					trickle_up(ancestors, (*op));//trickle up moving the new value up as high as it needs to go
					++size;
					break;
				}
			}
	}

	virtual void add_items(std::vector<ValType> const& vals, bool(*op)(ValType const& left, ValType const& right))
	{
		for (ValType val : vals)
			add_item(val, (*op));
	}

	virtual void remove_item(bool (*op)(ValType const& left, ValType const& right))
	{
		int last_spot;
		if (amount_full_tree(amount_complete_levels(size)) == size)//if this is a full tree, last spot in last level
			last_spot = amount_in_level(amount_complete_levels(size));
		else//otherwise, go onto last node in level
			last_spot = amount_last_level(size);

		int const max_of_last_level{ amount_in_level(amount_complete_levels(size)) };//know which direcion to head

		c_node<ValType> * * current{ &root };//to navigate, pointer to pointer to assign nullptr and delete correctly

		for (int current_level{ 0 }, previous_calc{ 0 }; true; ++current_level)
			if (last_spot <= previous_calc + max_of_last_level / amount_in_level(current_level + 1))//if the goal is leftward
				if ((*current)->left != nullptr)//go left
					current = &(*current)->left;
				else
				{
					std::swap(root->value, (*current)->value);//swap last item's and root's value only
					delete *current;
					*current = nullptr;
					if (root != nullptr)//no need to call if no root
						trickle_down((*op));
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
						trickle_down((*op));
					--size;
					break;
				}
			}
	}
	
	//takes a level and returns how many nodes could be side by side in it
	int static amount_in_level(int const& level)
	{
		return static_cast<int>(pow(2, level));
	}

	//takes an amount of levels and returns the amount of nodes that could fit into a tree of that size
	int static amount_full_tree(int const& levels)//reduced by one because four levels includes level 0
	{
		return static_cast<int>(pow(2, levels)) - 1;
	}

	//takes a size/amount of nodes in a tree and returns how many levels are full/complete in the tree
	int static amount_complete_levels(int const& sz)
	{
		int temp{ sz };
		for(int level{ 0 }; true; ++level)
		{
			if (temp - amount_in_level(level) < 0)
				return level;
			if (temp - amount_in_level(level) == 0)
				return  level + 1;
			temp -= amount_in_level(level);
		}
	}

	//takes a size and returns how many nodes are in the last level of the tree including zero if the tree is complete
	int static amount_last_level(int const& sz)
	{
		if (sz == 0)//when root is the last level, return 1 instead of 0
			return 1;
		return sz - amount_full_tree(amount_complete_levels(sz));
	}
};
