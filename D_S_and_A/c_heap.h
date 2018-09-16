#pragma once
#include <cmath>
#include "c_int_binary_tree.h"

//in a heap, always remove only the root
class c_heap : public c_int_binary_tree<c_node>//public c_tree<int>
{
public:
	int size;

	c_heap() = delete;

	explicit c_heap(int const& num) : c_int_binary_tree(num), size(1) {}

	virtual void add_item(int const& val) override = 0;//can't call the int binary tree add, heaps have different add orders

	/*void add_item(int const& val) override
	{
		c_node<int> * current = root;
		while(true)
		{
			if (current->left == nullptr)
				current->left = new c_node<int>{ val };
			else if (current->right == nullptr)
				current->right = new c_node<int>{ val };
			else
				current = current->right;//JUST FIGURED OUT THIS SEARCH WON't WORK, IT WOULD ALWAYS LEAD TO RIGHT MOST LEFT OR RIGHT LEAF
		}
	}*/

	virtual void add_items(std::vector<int> const& vals) override = 0;
	virtual void remove_item() = 0;
	
	//takes a level and returns how many nodes could be side by side in it
	int static amount_in_level(int const& level)
	{
		return pow(2, level);
		/*
		int amount = 1;
		for (int i = 1; i <= level; i++)
			amount = i * 2;
		return amount;
		*/
	}

	//takes an amount of levels and returns the amount of nodes that could fit into a tree of that size
	int static amount_full_tree(int const& levels)//reduced by one because four levels includes level 0
	{
		return pow(2, levels) - 1;

		//int amount = 1;
		//for (size_t i = 1; i <= levels - 1; ++i)
			//amount += amount_in_level(i);
		//return amount;
	}

	//takes a size/amount of nodes in a tree and returns how many levels are full/complete in the tree
	int static amount_complete_levels(int const& sz)
	{
		//take the size
		//start with level zero going up
		//subtract the amount in the level from the size
		//if the size - level amount <= 0
		//return level from level amount - 1

		int temp = sz;
		for(int level = 0; true; ++level)
		{
			//std::cout << temp << " - " << amount_in_level(level) << " = " << temp - amount_in_level(level) << std::endl;
			if (temp - amount_in_level(level) < 0)
			{
				//std::cout << "Returning: " << level << std::endl;
				return level;
			}
			if (temp - amount_in_level(level) == 0)
			{
				//std::cout << "Returning: " << level + 1 << std::endl;
				return  level + 1;
			}
			temp -= amount_in_level(level);
		}


		/*int temp = sz;
		for(int i = 1; true; ++i)
		{
			std::cout << temp << " - " << amount_in_level(i - 1) << std::endl;
			if (temp - amount_in_level(i - 1) <= 0)
				return i - 1;
			temp -= amount_in_level(i - 1);
		}*/
		
		//the theory here is that the amount in the level after the highest one the size could have, will have more nodes than the entire size
		
		//int levels = 0;
		//for(int i = 1; true; i++)
			//if (amount_in_level(i - 1) > sz)
				//return i;
		//for (int i = 0; amount_in_level(i) < sz; ++i)
			//if (amount_in_level(i) > sz)
				//return i;//no - 1 because it's a size type deal, the programmer should where needed
		//return 1;

		/*for (int i = 1; i < size; i *= 2)
			if (size > i)
				levels++;
		return levels;*/
	}

	//takes a size and returns how many nodes are in the last level of the tree including zero if the tree is complete
	int static amount_last_level(int const& sz)
	{
		return sz - amount_full_tree(amount_complete_levels(sz));
	}

	/*int calculate_levels() const
	{
		for(size_t nodes = 1, dividend = size, generations = 0; nodes < size; nodes *= 2, generations++)
			if(dividend - nodes > 0)
				dividend -= nodes;
			else
			{
				if (dividend > 0)
					generations++;
				return generations;
			}
		return 0;
	}*/
};
