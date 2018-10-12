#pragma once
#include "c_binary_tree.h"
#include "c_int_binary_funcs.h"

template<template<class> class NodeType>
class c_int_binary_tree : public c_binary_tree<int, NodeType>, public c_int_binary_funcs<NodeType>
{
public:
	c_int_binary_tree() = delete;

	explicit c_int_binary_tree(int const& val) : c_binary_tree<int, NodeType>(val) {}

	explicit c_int_binary_tree(std::vector<int> const& vals) : c_binary_tree<int, NodeType>(vals[0])
	{
		for (size_t i{ 1 }; i < vals.size(); ++i)//start at one, send first val off to be root
			this->c_int_binary_tree::add_item(vals[i]);
	}

	virtual void add_item(int const& val) override
	{
		NodeType<int> * current{ root };
		while (true)
			if (val < current->value)
			{
				if (current->left == nullptr)
				{
					current->left = new NodeType<int>{ val };
					break;
				}
				current = current->left;
			}
			else//greater than or equal to
			{
				if (current->right == nullptr)
				{
					current->right = new NodeType<int>{ val };
					break;
				}
				current = current->right;
			}
	}

	virtual void add_items(std::vector<int> const& vals) override
	{
		for (int val : vals)
			this->add_item(val);
	}

	void remove_item(int const& val) override
	{
		NodeType<int> * * found{ find_node(&root, val) };
		
		if(*found != nullptr)
			if((*found)->left == nullptr && (*found)->right == nullptr)
			{
				delete *found;
				*found = nullptr;
			}
			else if((*found)->right == nullptr)
				*found = (*found)->left;
			else if((*found)->left == nullptr)
				*found = (*found)->right;
			else//both child nodes exist
			{
				NodeType<int> * * current{ &(*found)->right };//search for the leftmost node of right child
				while(true)
					if ((*current)->left != nullptr)
						current = &(*current)->left;
					else
						break;
				(*found)->value = (*current)->value;//swap with next largest in tree

				if((*current)->right == nullptr)//delete node if all the way left
				{
					delete *current;
					*current = nullptr;
				}
				else//move right nodes up if it was purely the right node
					*current = (*current)->right;
			}
	}
};