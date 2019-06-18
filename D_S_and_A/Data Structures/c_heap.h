#pragma once

#include <cmath>
#include <vector>

#include "c_poly_node.h"
#include "c_binary_tree.h"

template<class DataType, class NodeType = c_poly_node<DataType>, typename Operation = std::greater<>>
class c_heap : public c_binary_tree<DataType, NodeType>
{
public:
	int size;

	c_heap() = delete;
	explicit c_heap(DataType const& val);
	explicit c_heap(std::vector<DataType> const& vals);

	//uses c_binary_tree's destructor

	void trickle_up(std::vector<NodeType * *> ancstrs) const;
	void trickle_down();

	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item();
	
	int static amount_in_level(int const& level);
	int static amount_full_tree(int const& levels);
	int static amount_complete_levels(int const& sz);
	int static amount_last_level(int const& sz);
};

#include "c_heap.inl"