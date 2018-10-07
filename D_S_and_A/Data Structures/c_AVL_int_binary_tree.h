#pragma once
#include "c_AVL_binary_tree.h"
#include "c_int_binary_funcs.h"

template<template<class> class NodeType>
class c_AVL_int_binary_tree : public c_AVL_binary_tree<int, NodeType>, public c_int_binary_funcs<NodeType>
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
					for (int i = ancestors.size() - 1; i >= 0; --i)//starting with the first possible grandparent, - 1 instead of - 2 because current wasn't added
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
					for (int i = ancestors.size() - 1; i >= 0; --i)//i must be int in these because when size_t/unsigned int goes below 0 it becomes a very high number
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

	void remove_item(int const& val) override
	{
		std::vector<NodeType<int> * *> ancestors{ find_node_with_path(&root, val) };

		if (*ancestors[ancestors.size() - 1] != nullptr)
			if ((*ancestors[ancestors.size() - 1])->left == nullptr && (*ancestors[ancestors.size() - 1])->right == nullptr)
			{
				delete *ancestors[ancestors.size() - 1];
				*ancestors[ancestors.size() - 1] = nullptr;
				for (int i = ancestors.size() - 1 - 1; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 2 to start at first possible grandparent
					rebalance(ancestors[i]);
			}
			else if ((*ancestors[ancestors.size() - 1])->right == nullptr)//only one child node exists, so just overwrite *found with that child
			{
				*ancestors[ancestors.size() - 1] = (*ancestors[ancestors.size() - 1])->left;
				for (int i = ancestors.size() - 1; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 1 to start at first possible grandparent, current
					rebalance(ancestors[i]);
			}
			else if ((*ancestors[ancestors.size() - 1])->left == nullptr)
			{
				*ancestors[ancestors.size() - 1] = (*ancestors[ancestors.size() - 1])->right;
				for (int i = ancestors.size() - 1; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 1 to start at first possible grandparent, current
					rebalance(ancestors[i]);
			}
			else//both child nodes exist
			{
				NodeType<int> * * current = &(*ancestors[ancestors.size() - 1])->right;//search for the leftmost node of right child
				while (true)
					if ((*current)->left != nullptr)
					{
						ancestors.push_back(current);//add the previous each time to rebalance later
						current = &(*current)->left;
					}
					else
						break;

				(*ancestors[ancestors.size() - 1])->value = (*current)->value;//swap with next largest in tree

				if ((*current)->right == nullptr)//delete node if all the way left
				{
					delete *current;
					*current = nullptr;
				}
				else//move right nodes up if it was purely the right node
					*current = (*current)->right;
				for (int i = ancestors.size() - 1 - 1; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 2 to start at first possible grandparent
					rebalance(ancestors[i]);
			}
	}
};
