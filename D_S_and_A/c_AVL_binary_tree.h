#pragma once
#include "c_binary_tree.h"

template <typename  ValType, template<class> class NodeType>
class c_AVL_binary_tree : c_binary_tree<ValType, NodeType>
{
public:
	c_AVL_binary_tree() = delete;

	explicit c_AVL_binary_tree(ValType const& val) : c_binary_tree(val) {}


};
