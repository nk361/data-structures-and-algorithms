#pragma once

#include "c_bst_iterator_in_order.h"

template<class DataType, class NodeType>
c_bst_iterator_in_order<DataType, NodeType>::c_bst_iterator_in_order(NodeType * * const& node)
{
	current = node;
	if((*node) != nullptr)//end() calls this constructor with nullptr
	{
		ancestors.push_back({ (*current), true });//this is just to add the node before the loop navigates/adds nodes, it's also needed in the case of a root that has no left child

		while ((*current)->children[0] != nullptr)
		{
			current = &(*current)->children[0];//assign current to the left most tree node
			ancestors.push_back({ (*current), true });//document ancestors it's encountered
		}
	}
}

template<class DataType, class NodeType>
c_bst_iterator_in_order<DataType, NodeType>& c_bst_iterator_in_order<DataType, NodeType>::operator++()
{
	//3 posibilities, left, right, up to parent
	//but also a check for the rightmost node to change to a proper end

	if((*current)->children[1] == nullptr)//if there's no right child, check if it's rightmost
	{
		if (ancestors.size() == 1 && ancestors.back().first->children[0] == nullptr && ancestors.back().first->children[1] == nullptr)//if there's only a root, mark it as fully explored so it can be rightmost
			ancestors.back().second = false;

		bool rightmost = true;
		for(std::pair<NodeType *, bool> ancestor : ancestors)//check that all ancestors have been fully explored
			if(ancestor.second)//top to bottom checking has a higher chance of finding a true value FASTER than bottom to top
			{
				rightmost = false;
				break;
			}

		if (rightmost)//set current to it's nullptr right child to be compared to end() for the tree to be iterable
			current = &(*current)->children[1];
	}
	
	if ((*current) != nullptr)//the end code above just set current to null, no navigation
		if ((*current)->children[0] != nullptr && (ancestors.empty() || (*current) != (ancestors.back().first)))//go left if the node has a left child and the current node is not yet added to ancestors
		{
			ancestors.push_back({ (*current), true });//add node to ancestors no matter what

			current = &(*current)->children[0];

			while ((*current)->children[0] != nullptr)//go left as much as possible, adding nodes encountered to ancestors except the last
			{
				ancestors.push_back({ (*current), true });
				current = &(*current)->children[0];
			}
		}
		else if ((*current)->children[1] != nullptr && ((ancestors.empty() || (*current) != ancestors.back().first) || ancestors.back().second))//go right if the current node could not go left and has a right child and either it's not already added to ancestors or the current node is marked to go right on
		{
			if ((*current) != ancestors.back().first)//if the node has no left child, it hasn't been encountered and needs added to ancestors, otherwise, change the node to say we're going right
				ancestors.push_back({ (*current), false });
			else
				ancestors.back().second = false;

			current = &(*current)->children[1];

			while ((*current)->children[0] != nullptr)//go left as much as possible, adding nodes encountered to ancestors except the last
			{
				ancestors.push_back({ (*current), true });
				current = &(*current)->children[0];
			}
		}
		else if (!(ancestors.size() == 1 && ancestors.back().first->children[1] == nullptr))//go up to parent, ignoring the special case of the not fully explored root with no right child, which needs stopped on and for its second to be updated to false
		{
			if (ancestors.back().first != (*current) && (*current)->children[0] == nullptr && (*current)->children[1] == nullptr)
				ancestors.push_back({ (*current), false });//add the leaf node to ancestors so it can return to parent properly

			ancestors.pop_back();

			current = &ancestors.back().first;

			while (!ancestors.back().second && !(ancestors.back().first->children[0] != nullptr && ancestors.back().first->children[1] == nullptr))//if the node is fully explored and does NOT have only one, left child don't stop on it, instead loop up the tree
			{
				ancestors.pop_back();
				current = &ancestors.back().first;
			}

			if ((*current)->children[1] == nullptr)//when returning to a parent that has no right child, second must be set to false incase it is the rightmost node
				ancestors.back().second = false;
		}
	return *this;
}

template<class DataType, class NodeType>
c_bst_iterator_in_order<DataType, NodeType> c_bst_iterator_in_order<DataType, NodeType>::operator++(int)//postfix
{
	c_bst_iterator_in_order<DataType, NodeType> temp = *this; ++*this; return temp;
}

template<class DataType, class NodeType>
bool c_bst_iterator_in_order<DataType, NodeType>::operator==(c_bst_iterator_in_order<DataType, NodeType> other) const
{
	return *current == **other;
}

template<class DataType, class NodeType>
bool c_bst_iterator_in_order<DataType, NodeType>::operator!=(c_bst_iterator_in_order<DataType, NodeType> const& other) const
{
	return !(*this == other);
}

template<class DataType, class NodeType>
NodeType * * c_bst_iterator_in_order<DataType, NodeType>::operator*()
{
	return current;
}