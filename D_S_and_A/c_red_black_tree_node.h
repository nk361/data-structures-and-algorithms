#pragma once
#include "c_node.h"

template <class MyType>
class c_red_black_tree_node : public c_node<MyType>
{
public:
	bool red = true;
};
