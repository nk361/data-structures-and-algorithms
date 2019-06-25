#pragma once

#include <vector>

#include "c_heap.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_min_heap : public c_heap<DataType, NodeType, std::less<>>
{
public:
	c_min_heap() = delete;
	explicit c_min_heap(DataType const& val);
	explicit c_min_heap(std::vector<DataType> const& vals);

	DataType get_top() override;
	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item() override;
};

#include "c_min_heap.inl"