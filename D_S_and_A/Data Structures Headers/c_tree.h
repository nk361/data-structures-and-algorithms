#pragma once
#include <vector>

#include "c_poly_node.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_tree
{
public:
	NodeType * root;

	c_tree() = delete;

	explicit c_tree(DataType const& val);

	~c_tree();//not virtual because of unique tree navigation

	virtual void add_item(DataType const& val) = 0;
	virtual void add_items(std::vector<DataType> const& vals) = 0;
	virtual void remove_item(DataType const& val) = 0;
};

#include "c_tree.inl"