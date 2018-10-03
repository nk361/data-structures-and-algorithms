#pragma once

//This header is to be included in all binary trees that deal with purely ints that follow the rule of larger values go right, smaller go left
template<template<class> class NodeType>
class c_int_binary_funcs
{
public:
	NodeType<int> * * find_node(int const& val, NodeType<int> * * rt)//take and return pointer to pointer so the node in the tree can be changed
	{
		NodeType<int> * * current = rt;
		while (true)
		{
			if ((*current)->value == val)
				return current;
			if (val < (*current)->value)
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

	//Lowest common ancestor node
	//This function takes the current root by reference and two values
	//It loops through looking for the FIRST node that would make the two values split paths in the tree
	//If one or both values could not be located in the tree, this returns a pointer to nullptr
	//It returns a pointer to the lca node so that it can be changed
	NodeType<int> * * lca(NodeType<int> * * rt, int const& val1, int const& val2)
	{
		NodeType<int> * * current = rt;
		if ((*find_node(val1, rt) != nullptr) && (*find_node(val2, rt)) != nullptr)
			while (true)
				if (val1 < (*current)->value && val2 < (*current)->value)
					current = &(*current)->left;
				else if (val1 > (*current)->value && val2 > (*current)->value)
					current = &(*current)->right;
				else
					return current;
		return *find_node(val1, rt) == nullptr ? find_node(val1, rt) : find_node(val2, rt);//return pointer to nullptr
	}
};