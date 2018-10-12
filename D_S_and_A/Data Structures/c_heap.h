#pragma once
#include <cmath>
#include "c_node.h"
#include "c_binary_tree.h"

//in a heap, always remove only the root
template <class ValType>
class c_heap : public c_binary_tree<ValType, c_node>
{
public:
	int size;

	c_heap() = delete;

	explicit c_heap(int const& num) : c_binary_tree(num), size(1) {}

	virtual void add_item(int const& val) override = 0;

	virtual void add_items(std::vector<int> const& vals) override = 0;

	virtual void remove_item() = 0;//purposely hide remove from c_binary_tree for this with no param
	
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
