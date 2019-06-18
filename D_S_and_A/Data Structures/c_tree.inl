#pragma once

#include <vector>

#include "c_tree.h"

template<class DataType, class NodeType>
c_tree<DataType, NodeType>::c_tree(DataType const& val)
{
	root = new NodeType{ val, 2 };
}

template<class DataType, class NodeType>
c_tree<DataType, NodeType>::~c_tree()//not virtual because of unique tree navigation
{
	if (root != nullptr)//incase root was all that was left and it was removed
	{
		NodeType * * current{ &root };//made to navigate without changing tree pointer values unless intended
		std::vector<NodeType * *> ancestors{ { current } };//using this vector like a stack
		while (true)
		{
			for (int i{ 0 }; i < static_cast<int>((*current)->children.size()); ++i)//look through all children for one that isn't null to become current
				if ((*current)->children[i] != nullptr)
				{
					current = &((*current)->children[i]);
					ancestors.push_back(current);
					break;
				}

			bool all_null{ true };//check if the current node has only null children
			for (int i{ 0 }; i < static_cast<int>((*current)->children.size()); ++i)
				if ((*current)->children[i] != nullptr)
					all_null = false;

			if (all_null)//remove current node
			{
				ancestors.pop_back();

				delete *current;
				*current = nullptr;

				if (root == nullptr)//tree deleted
					break;

				current = ancestors.back();//go back up one parent
			}
		}
	}
}