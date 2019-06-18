#pragma once

#include "c_bst_sorts.h"

//big O depends on the binary search tree
template<class DataType, class NodeType, typename Operation, class TreeType>//accounting for template needs of the tree classes
std::vector<DataType>& c_bst_sorts<DataType, NodeType, Operation, TreeType>::sort(std::vector<DataType>& arr)
{
	TreeType bst{ arr[0] };//add all items to bst
	for (int i{ 1 }; i < static_cast<int>(arr.size()); ++i)//start at 1 since the first item was made root
		bst.add_item(arr[i]);

	//in order traversal left root right
	int index{ 0 };//for incrementing through the array with each added tree value
	for(NodeType * * current : bst)
	{
		arr[index] = (*current)->value;
		++index;
	}
	
	return arr;
}