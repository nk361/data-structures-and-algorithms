#pragma once
#include "c_bst_sorts.h"

template <class MyType, template <class ValType, template <class> class NodeType> class BstType, template <class> class NodeType>//accounting for template needs of the tree classes
std::vector<MyType>& c_bst_sorts<MyType, BstType, NodeType>::sort(std::vector<MyType>& arr)
{
	BstType<MyType, NodeType> bst{ arr[0] };//add all items to bst
	for (int i{ 1 }; i < arr.size(); ++i)//start at 1 since the first item was made root
		bst.add_item(arr[i]);

	//in order traversal left root right
	int index = 0;//for incrementing through the array with each added tree value
	NodeType<MyType> * current{ bst.root };
	std::vector<std::pair<NodeType<MyType> *, bool>> ancestors;//store the previous nodes and the direction it went from it
	ancestors.push_back({ current, current->children[0] != nullptr ? true : false });//true shows it went left, false shows it went right
	while (true)
	{
		if (current->children[0] == nullptr && current->children[1] == nullptr)//do this first incase the bool says go right, but there's nothing right either
		{
			arr[index] = ancestors.back().first->value;//add leaf node
			++index;//not in the line above for clarity
			ancestors.pop_back();//you know the current node is a leaf node, so you can pop it with no worries

			for (size_t i = ancestors.size() - 1; true; --i)//loop to look for the next path or exit if reached the end
			{
				if (ancestors.empty())//went all the way up to root without another path
					break;
				if (ancestors[i].second && ancestors[i].first->children[1] != nullptr)//found an ancestor with an unexplored right node
				{
					ancestors[i].second = false;//go right on this node
					current = ancestors[i].first;
					break;
				}
				if (index < arr.size() && ancestors.back().second)
				{
					arr[index] = ancestors.back().first->value;//add node on the way back up if it has been encountered only the first time
					++index;
				}

				ancestors.pop_back();
			}
			if (ancestors.empty())//break from for loop AND while loop
				break;
		}
		if (ancestors.back().second)//go left
			current = current->children[0];
		else//go right
		{
			arr[index] = current->value;//add parent node only when heading right
			++index;
			current = current->children[1];
		}

		ancestors.push_back({ current, current->children[0] != nullptr ? true : false });//this after checks because of initial value
	}

	return arr;
}