#pragma once

//This header is to be included in all binary trees that deal with purely ints that follow the rule of larger values go right, smaller go left
template<template<class> class NodeType>
class c_int_binary_funcs
{
public:
	NodeType<int> * * find_node(NodeType<int> * * rt, int const& val)//take and return pointer to pointer so the node in the tree can be changed
	{
		NodeType<int> * * current{ rt };
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

	//This function works the same as find_node, except it keeps track of ancestors along the way
	//It returns a vector with pointers to pointers of the ancestors with the last element being the found node
	std::vector<NodeType<int> * *> find_node_with_path(NodeType<int> * * rt, int const& val)
	{
		NodeType<int> * * current{ rt };
		std::vector<NodeType<int> * *> ancestors{ rt };
		while (true)
		{
			if ((*current)->value == val)
				return ancestors;
			if (val < (*current)->value)
			{
				if ((*current)->left == nullptr)
					return {};//returning an empty list
				current = &(*current)->left;
			}
			else
			{
				if ((*current)->right == nullptr)
					return {};
				current = &(*current)->right;
			}
			ancestors.push_back(current);
		}
	}

	//Lowest common ancestor node
	//This function takes the current root by reference and two values
	//It loops through looking for the FIRST node that would make the two values split paths in the tree
	//If one or both values could not be located in the tree, this returns a pointer to nullptr
	//It returns a pointer to the lca node so that it can be changed
	NodeType<int> * * lca(NodeType<int> * * rt, int const& val1, int const& val2)
	{
		NodeType<int> * * current{ rt };
		if ((*find_node(rt, val1) != nullptr) && (*find_node(rt, val2)) != nullptr)
			while (true)
				if (val1 < (*current)->value && val2 < (*current)->value)
					current = &(*current)->left;
				else if (val1 > (*current)->value && val2 > (*current)->value)
					current = &(*current)->right;
				else
					return current;
		return *find_node(rt, val1) == nullptr ? find_node(rt, val1) : find_node(rt, val2);//return pointer to nullptr, would like a better way
	}

	size_t depth(NodeType<int> * rt, int const& val)
	{
		int count{ 1 };
		NodeType<int> * current{ rt };
		while (true)
		{
			if (current->value == val)
				return count;
			if (val < current->value)
				current = current->left;
			else
				current = current->right;
			++count;
		}
	}
};