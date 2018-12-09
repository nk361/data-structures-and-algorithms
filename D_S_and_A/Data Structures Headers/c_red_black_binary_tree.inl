#pragma once
#include "c_red_black_binary_tree.h"

template<typename ValType, template<class> class NodeType>
c_red_black_binary_tree<ValType, NodeType>::c_red_black_binary_tree(ValType const& val) : c_binary_tree<ValType, NodeType>(val) {}

template<typename ValType, template<class> class NodeType>
c_red_black_binary_tree<ValType, NodeType>::c_red_black_binary_tree(std::vector<ValType> const& vals) : c_binary_tree<ValType, NodeType>(vals[0])
{
	c_tree<ValType, NodeType>::root->red = false;
	for (size_t i{ 1 }; i < vals.size(); ++i)
		c_red_black_binary_tree<ValType, NodeType>::add_item(vals[i]);
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::add_item(ValType const& val)
{
	NodeType<ValType> * * current{ &(c_tree<ValType, NodeType>::root) };//pointer to pointer so that pointer references can change originals
	std::vector<NodeType<ValType> * *> ancestors;

	while (true)
		if (val < (*current)->value)
		{
			if ((*current)->children[0] == nullptr)
			{
				(*current)->children[0] = new NodeType<ValType>{ val, 2 };
				for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//starting with the first possible grandparent, - 1 instead of - 2 because current wasn't added
					rebalance(ancestors[i]);
				if (c_tree<ValType, NodeType>::root->red)//root is always black
					c_tree<ValType, NodeType>::root->red = false;
				break;
			}
			ancestors.push_back(current);
			current = &(*current)->children[0];
		}
		else//greater than or equal to
		{
			if ((*current)->children[1] == nullptr)
			{
				(*current)->children[1] = new NodeType<ValType>{ val, 2 };
				for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//i must be int in these because when size_t/unsigned int goes below 0 it becomes a very high number
					rebalance(ancestors[i]);
				if (c_tree<ValType, NodeType>::root->red)//root is always black
					c_tree<ValType, NodeType>::root->red = false;
				break;
			}
			ancestors.push_back(current);
			current = &(*current)->children[1];
		}
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	for (ValType val : vals)
		c_red_black_binary_tree<ValType, NodeType>::add_item(val);
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::remove_item(ValType const& val)
{
	std::vector<NodeType<ValType> * *> ancestors{ c_binary_tree<ValType, NodeType>::find_node_with_path(&(c_tree<ValType, NodeType>::root), val) };

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
			NodeType<ValType> * * current{ &(*ancestors[ancestors.size() - 1])->children[1] };//search for the leftmost node of right child
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

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::color_flip(NodeType<ValType> * * grandparent)
{
	(*grandparent)->red = true;
	(*grandparent)->children[0]->red = false;
	(*grandparent)->children[1]->red = false;
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::rebalance(NodeType<ValType> * * grandparent)
{
	if ((*grandparent)->children[0] != nullptr && (*grandparent)->children[0]->red)//check left
		if ((*grandparent)->children[0]->children[0] != nullptr && (*grandparent)->children[0]->children[0]->red)//check left's left
			if ((*grandparent)->children[1] != nullptr && (*grandparent)->children[1]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_binary_tree<ValType, NodeType>::rotate_right(*grandparent);
				(*grandparent)->red = false;
				//left child is already red
				(*grandparent)->children[1]->red = true;
			}
		else if ((*grandparent)->children[0]->children[1] != nullptr && (*grandparent)->children[0]->children[1]->red)//check left's right
			if ((*grandparent)->children[1] != nullptr && (*grandparent)->children[1]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_binary_tree<ValType, NodeType>::rotate_left_right(*grandparent);
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
				*grandparent = c_binary_tree<ValType, NodeType>::rotate_right_left(*grandparent);
				(*grandparent)->red = false;
				(*grandparent)->children[0]->red = true;
				//right child is already red
			}
		else if ((*grandparent)->children[1]->children[1] != nullptr && (*grandparent)->children[1]->children[1]->red)//check right's right
			if ((*grandparent)->children[0] != nullptr && (*grandparent)->children[0]->red)//check aunt
				color_flip(grandparent);
			else
			{
				*grandparent = c_binary_tree<ValType, NodeType>::rotate_left(*grandparent);
				(*grandparent)->red = false;
				(*grandparent)->children[0]->red = true;
				//right child is already red
			}
}