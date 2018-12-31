#pragma once
#include "c_avl_binary_tree.h"

template<class ValType, template<class> class NodeType, typename Operation>
c_avl_binary_tree<ValType, NodeType, Operation>::c_avl_binary_tree(ValType const& val) : c_binary_tree<ValType, NodeType, Operation>(val) {}

template<class ValType, template<class> class NodeType, typename Operation>
c_avl_binary_tree<ValType, NodeType, Operation>::c_avl_binary_tree(std::vector<ValType> const& vals) : c_binary_tree<ValType, NodeType, Operation>(vals[0])
{
	for (size_t i{ 1 }; i < vals.size(); ++i)
		c_avl_binary_tree<ValType, NodeType, Operation>::add_item(vals[i]);
}

template<class ValType, template<class> class NodeType, typename Operation>
void c_avl_binary_tree<ValType, NodeType, Operation>::add_item(ValType const& val)
{
	Operation const op = Operation();

	NodeType<ValType> * * current{ &(c_avl_binary_tree<ValType, NodeType, Operation>::root) };//pointer to pointer so that pointer references can change originals
	std::vector<NodeType<ValType> * *> ancestors;

	while (true)
		if (op(val, (*current)->value))
		{
			if ((*current)->children[0] == nullptr)
			{
				(*current)->children[0] = new NodeType<ValType>{ val, 2 };
				for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//starting with the first possible grandparent, - 1 instead of - 2 because current wasn't added
					rebalance(ancestors[i]);
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
				break;
			}
			ancestors.push_back(current);
			current = &(*current)->children[1];
		}
}

template<class ValType, template<class> class NodeType, typename Operation>
void c_avl_binary_tree<ValType, NodeType, Operation>::add_items(std::vector<ValType> const& vals)
{
	for (ValType val : vals)
		c_avl_binary_tree<ValType, NodeType, Operation>::add_item(val);
}

template<class ValType, template<class> class NodeType, typename Operation>
void c_avl_binary_tree<ValType, NodeType, Operation>::remove_item(ValType const& val)
{
	std::vector<NodeType<ValType> * *> ancestors{ c_avl_binary_tree<ValType, NodeType, Operation>::find_node_with_path(&(c_avl_binary_tree<ValType, NodeType, Operation>::root), val) };

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

template<class ValType, template<class> class NodeType, typename Operation>
size_t c_avl_binary_tree<ValType, NodeType, Operation>::height(NodeType<ValType> * r_avl_node)
{
	if (r_avl_node == nullptr)
		return 0;

	size_t max_height = 1;
	NodeType<ValType> * current{ r_avl_node };
	std::vector<std::pair<NodeType<ValType> *, bool>> ancestors;//store the previous nodes and the direction it went from it
	ancestors.push_back({ current, current->children[0] != nullptr ? true : false });//true shows it went left, false shows it went right
	while (true)
	{
		if (current->children[0] == nullptr && current->children[1] == nullptr)//do this first incase the bool says go right, but there's nothing right either
		{
			if (ancestors.size() > max_height)//check for new record height
				max_height = ancestors.size();

			ancestors.pop_back();//you know the current node is a leaf node, so you can pop it with no worries

			for (size_t i = ancestors.size() - 1; true; --i)//loop to look for the next path or exit if reached the end
			{
				if (ancestors.empty())//went all the way up to root without another path
					return max_height;
				if (ancestors[i].second && ancestors[i].first->children[1] != nullptr)//found an ancestor with an unexplored right node
				{
					ancestors[i].second = false;//go right on this node
					current = ancestors[i].first;
					break;
				}
				ancestors.pop_back();
			}
		}

		if (ancestors.back().second)//go left
			current = current->children[0];
		else//go right
			current = current->children[1];

		ancestors.push_back({ current, current->children[0] != nullptr ? true : false });//this after checks because of initial value
	}
}

template<class ValType, template<class> class NodeType, typename Operation>
void c_avl_binary_tree<ValType, NodeType, Operation>::rebalance(NodeType<ValType> * * chain_node)//call this with a reference to the grandparent
{
	if (static_cast<int>(height((*chain_node)->children[0]) - height((*chain_node)->children[1])) > 1)//violation on left
		if (height((*chain_node)->children[0]->children[0]) > height((*chain_node)->children[0]->children[1]))//right rotation needed
			*chain_node = c_avl_binary_tree<ValType, NodeType, Operation>::rotate_right((*chain_node));
		else//left right rotation needed
			*chain_node = c_avl_binary_tree<ValType, NodeType, Operation>::rotate_left_right((*chain_node));
	else if (static_cast<int>(height((*chain_node)->children[0]) - height((*chain_node)->children[1])) < -1)//violation on right, check needed for calls on balanced nodes instead of just else
		if (height((*chain_node)->children[1]->children[0]) < height((*chain_node)->children[1]->children[1]))//left rotation needed
			*chain_node = c_avl_binary_tree<ValType, NodeType, Operation>::rotate_left((*chain_node));
		else//right left rotation needed
			*chain_node = c_avl_binary_tree<ValType, NodeType, Operation>::rotate_right_left((*chain_node));
}