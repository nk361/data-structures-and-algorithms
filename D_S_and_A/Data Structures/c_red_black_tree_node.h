#pragma once
#include "c_node.h"

template <typename  ValType>
class c_red_black_tree_node : public c_node<ValType>
{
public:
	bool red{ true };
};