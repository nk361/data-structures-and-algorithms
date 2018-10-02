#pragma once
#include "c_AVL_binary_tree.h"

template<template<class> class NodeType>
class c_AVL_int_binary_tree : public c_AVL_binary_tree<int, NodeType>//, public c_int_binary_tree<NodeType>
{
public:
	c_AVL_int_binary_tree() = delete;

	explicit c_AVL_int_binary_tree(int const& val) : c_AVL_binary_tree<int, NodeType>(val) {}

	explicit c_AVL_int_binary_tree(std::vector<int> const& vals) : c_AVL_binary_tree<int, NodeType>(vals[0])
	{
		for (size_t i = 1; i < vals.size(); ++i)
			this->c_AVL_int_binary_tree::add_item(vals[i]);
	}

	void add_item(int const& val) override
	{
		NodeType<int> * * current = &root;//pointer to pointer so that pointer references can change originals
		std::vector<NodeType<int> * *> ancestors;

		while(true)
			if (val < (*current)->value)
			{
				if ((*current)->left == nullptr)
				{
					(*current)->left = new NodeType<int>{ val };
					for (int i = ancestors.size() - 1; i >= 0; --i)//only starting at size minus 1 because this ^ new node wasn't added to ancestors
						rebalance(ancestors[i]);
					break;
				}
				ancestors.push_back(current);
				current = &(*current)->left;
			}
			else//greater than or equal to
			{
				if ((*current)->right == nullptr)
				{
					(*current)->right = new NodeType<int>{ val };
					for (int i = ancestors.size() - 1; i >= 0; --i)
						rebalance(ancestors[i]);
					break;
				}
				ancestors.push_back(current);
				current = &(*current)->right;
			}
	}

	void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	//for now I'll copy these from c_int_binary_tree, but I think I can get them here through inheritance somehow
	NodeType<int> * * find_node(int const& val)//return pointer to pointer so the node in the tree can be changed
	{
		NodeType<int> * * current = &root;
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

	void remove_item(int const& val) override
	{
		NodeType<int> * * found = find_node(val);

		if (*found != nullptr)
			if ((*found)->left == nullptr && (*found)->right == nullptr)
			{
				delete *found;
				*found = nullptr;
			}
			else if ((*found)->right == nullptr)
				*found = (*found)->left;
			else if ((*found)->left == nullptr)
				*found = (*found)->right;
			else//both child nodes exist
			{
				NodeType<int> * * current = &(*found)->right;//search for the leftmost node of right child
				while (true)
					if ((*current)->left != nullptr)
						current = &(*current)->left;
					else
						break;
				(*found)->value = (*current)->value;//swap with next largest in tree

				if ((*current)->right == nullptr)//delete node if all the way left
				{
					delete *current;
					*current = nullptr;
				}
				else//move right nodes up if it was purely the right node
					*current = (*current)->right;
			}
	}
};
