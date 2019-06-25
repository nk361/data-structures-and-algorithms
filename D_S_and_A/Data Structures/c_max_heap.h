#pragma once

#include <vector>

#include "c_poly_node.h"
#include "c_heap.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_max_heap : public c_heap<DataType, NodeType, std::greater<>>
{
public:
	c_max_heap() = delete;
	explicit c_max_heap(DataType const& val);
	explicit c_max_heap(std::vector<DataType> const& vals);

	DataType get_top() override;
	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item() override;
};

#include "c_max_heap.inl"