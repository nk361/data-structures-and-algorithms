#pragma once

#include <vector>

#include "c_binary_tree.h"
#include "c_red_black_binary_tree.h"

template<class DataType, class NodeType, typename Operation>
c_red_black_binary_tree<DataType, NodeType, Operation>::c_red_black_binary_tree(DataType const& val) : c_binary_tree<DataType, NodeType, Operation>(val) {}

template<class DataType, class NodeType, typename Operation>
c_red_black_binary_tree<DataType, NodeType, Operation>::c_red_black_binary_tree(std::vector<DataType> const& vals) : c_binary_tree<DataType, NodeType, Operation>(vals[0])
{
	c_red_black_binary_tree<DataType, NodeType, Operation>::root->red = false;
	for (size_t i{ 1 }; i < vals.size(); ++i)
		c_red_black_binary_tree<DataType, NodeType, Operation>::add_item(vals[i]);
}

template<class DataType, class NodeType, typename Operation>
void c_red_black_binary_tree<DataType, NodeType, Operation>::add_item(DataType const& val)
{
	Operation const op = Operation();

	NodeType * * current{ &(c_red_black_binary_tree<DataType, NodeType, Operation>::root) };//pointer to pointer so that pointer references can change originals
	std::vector<NodeType * *> ancestors;

	while (true)
		if (op(val, (*current)->value))
		{
			if ((*current)->children[0] == nullptr)
			{
				(*current)->children[0] = new NodeType{ val, 2 };
				for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//starting with the first possible grandparent, - 1 instead of - 2 because current wasn't added
					rebalance(ancestors[i]);
				if (c_red_black_binary_tree<DataType, NodeType, Operation>::root->red)//root is always black
					c_red_black_binary_tree<DataType, NodeType, Operation>::root->red = false;
				break;
			}
			ancestors.push_back(current);
			current = &(*current)->children[0];
		}
		else//greater than or equal to
		{
			if ((*current)->children[1] == nullptr)
			{
				(*current)->children[1] = new NodeType{ val, 2 };
				for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//i must be int in these because when size_t/unsigned int goes below 0 it becomes a very high number
					rebalance(ancestors[i]);
				if (c_red_black_binary_tree<DataType, NodeType, Operation>::root->red)//root is always black
					c_red_black_binary_tree<DataType, NodeType, Operation>::root->red = false;
				break;
			}
			ancestors.push_back(current);
			current = &(*current)->children[1];
		}
}

template<class DataType, class NodeType, typename Operation>
void c_red_black_binary_tree<DataType, NodeType, Operation>::add_items(std::vector<DataType> const& vals)
{
	for (DataType val : vals)
		c_red_black_binary_tree<DataType, NodeType, Operation>::add_item(val);
}

template<class DataType, class NodeType, typename Operation>
void c_red_black_binary_tree<DataType, NodeType, Operation>::remove_item(DataType const& val)
{
	std::vector<NodeType * *> ancestors{ c_red_black_binary_tree<DataType, NodeType, Operation>::find_node_with_path(&(c_red_black_binary_tree<DataType, NodeType, Operation>::root), val) };

	if (*ancestors[ancestors.size() - 1] != nullptr)
		if ((*ancestors[ancestors.size() - 1])->children[0] == nullptr && (*ancestors[ancestors.size() - 1])->children[1] == nullptr)
		{
			delete *ancestors[ancestors.size() - 1];
			*ancestors[ancestors.size() - 1] = nullptr;
			for (int i{ static_cast<int>(ancestors.size()) - 1 - 1 }; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 2 to start at first possible grandparent
				rebalance(ancestors[i]);
		}
		else if ((*ancestors[ancestors.size() - 1])->children[1] == nullptr)//only one child node exists, so just overwrite *found with that child
		{
			*ancestors[ancestors.size() - 1] = (*ancestors[ancestors.size() - 1])->children[0];
			for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 1 to start at first possible grandparent, current
				rebalance(ancestors[i]);
		}
		else if ((*ancestors[ancestors.size() - 1])->children[0] == nullptr)
		{
			*ancestors[ancestors.size() - 1] = (*ancestors[ancestors.size() - 1])->children[1];
			for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 1 to start at first possible grandparent, current
				rebalance(ancestors[i]);
		}
		else//both child nodes exist
		{
			NodeType * * current{ &(*ancestors[ancestors.size() - 1])->children[1] };//search for the leftmost node of right child
			while (true)
				if ((*current)->children[0] != nullptr)
				{
					ancestors.push_back(current);//add the previous each time to rebalance later
					current = &(*current)->children[0];
				}
				else
					break;

			(*ancestors[ancestors.size() - 1])->value = (*current)->value;//swap with next largest in tree

			if ((*current)->children[1] == nullptr)//delete node if all the way left
			{
				delete *current;
				*current = nullptr;
			}
			else//move right nodes up if it was purely the right node
				*current = (*current)->children[1];
			for (int i{ static_cast<int>(ancestors.size()) - 1 - 1 }; i >= 0; --i)//i must be int type, size_t cannot go less than zero, - 2 to start at first possible grandparent
				rebalance(ancestors[i]);
		}
}

template<class DataType, class NodeType, typename Operation>
void c_red_black_binary_tree<DataType, NodeType, Operation>::color_flip(NodeType * * grandparent)
{
	(*grandparent)->red = true;
	(*grandparent)->children[0]->red = false;
	(*grandparent)->children[1]->red = false;
}

template<class DataType, class NodeType, typename Operation>
void c_red_black_binary_tree<DataType, NodeType, Operation>::rebalance(NodeType * * grandparent)
{
	if ((*grandparent)->children[0] != nullptr && (*grandparent)->children[0]->red)//check left
		if ((*grandparent)->children[0]->children[0] != nullptr && (*grandparent)->children[0]->children[0]->red)//check left's left
			if ((*grandparent)->children[1] != nullptr && (*grandparent)->children[1]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_red_black_binary_tree<DataType, NodeType, Operation>::rotate_right(*grandparent);
				(*grandparent)->red = false;
				//left child is already red
				(*grandparent)->children[1]->red = true;
			}
		else if ((*grandparent)->children[0]->children[1] != nullptr && (*grandparent)->children[0]->children[1]->red)//check left's right
			if ((*grandparent)->children[1] != nullptr && (*grandparent)->children[1]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_red_black_binary_tree<DataType, NodeType, Operation>::rotate_left_right(*grandparent);
				(*grandparent)->red = false;
				//left child is already red
				(*grandparent)->children[1]->red = true;
			}
	if ((*grandparent)->children[1] != nullptr && (*grandparent)->children[1]->red)//check right //not if else because red aunts can go into first if
		if ((*grandparent)->children[1]->children[0] != nullptr && (*grandparent)->children[1]->children[0]->red)//check right's left
			if ((*grandparent)->children[0] != nullptr && (*grandparent)->children[0]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_red_black_binary_tree<DataType, NodeType, Operation>::rotate_right_left(*grandparent);
				(*grandparent)->red = false;
				(*grandparent)->children[0]->red = true;
				//right child is already red
			}
		else if ((*grandparent)->children[1]->children[1] != nullptr && (*grandparent)->children[1]->children[1]->red)//check right's right
			if ((*grandparent)->children[0] != nullptr && (*grandparent)->children[0]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_red_black_binary_tree<DataType, NodeType, Operation>::rotate_left(*grandparent);
				(*grandparent)->red = false;
				(*grandparent)->children[0]->red = true;
				//right child is already red
			}
}