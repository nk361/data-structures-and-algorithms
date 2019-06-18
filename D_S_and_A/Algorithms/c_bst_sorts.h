#pragma once

#include <vector>
#include "../Data Structures/c_red_black_poly_node.h"
#include "../Data Structures/c_red_black_binary_tree.h"

template<class DataType, class NodeType = c_red_black_poly_node<DataType>, typename Operation = std::less<>, class TreeType = c_red_black_binary_tree<DataType, NodeType, Operation>>
class c_bst_sorts
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_bst_sorts.inl"