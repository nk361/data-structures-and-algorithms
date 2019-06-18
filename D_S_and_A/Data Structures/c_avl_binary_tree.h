#pragma once

#include <vector>

#include "c_binary_tree.h"

template<class DataType, class NodeType = c_poly_node<DataType>, typename Operation = std::less<>>
class c_avl_binary_tree : public c_binary_tree<DataType, NodeType, Operation>
{
public:
	c_avl_binary_tree() = delete;
	explicit c_avl_binary_tree(DataType const& val);
	explicit c_avl_binary_tree(std::vector<DataType> const& vals);

	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item(DataType const& val) override;

	size_t height(NodeType * r_avl_node);
	void rebalance(NodeType * * chain_node);//call this with a reference to the grandparent
};

#include "c_avl_binary_tree.inl"