#pragma once

#include <vector>

#include "c_poly_node.h"
#include "c_max_heap.h"
#include "c_heap_interface.h"

template <class DataType, class HeapType = c_max_heap<DataType, c_poly_node<DataType>>>//TODO update this to be the fibonacci heap when it is completed
class c_priority_queue : public c_heap_interface<DataType>
{
public:
	HeapType heap;//type must have get_top, add_item, add_items, and remove_item functions

	c_priority_queue() = delete;
	explicit c_priority_queue(DataType const& val);
	explicit c_priority_queue(std::vector<DataType> const& vals);

	DataType get_top() override;
	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item() override;
};

#include "c_priority_queue.inl"