#pragma once
#include "c_heap.h"

template <typename ValType>
class c_max_heap : public c_heap<ValType>
{
public:
	//this is the only difference to min heap and the one in the vector param constructor
	bool (*greater_than)(ValType const&, ValType const&) { [](ValType const& left, ValType const& right) { return left > right; } };
	
	c_max_heap() = delete;

	explicit c_max_heap(ValType const& val) : c_heap<ValType>(val) {}

	//must give default param value here of the lambda because otherwise greater_than is not initialized when c_heap's constructor needs it (this also means greater than can be changed with a second param)
	explicit c_max_heap(std::vector<ValType> const& vals, bool(*greater_than)(ValType const&, ValType const&) = [](ValType const& left, ValType const& right) { return left > right; })
	: c_heap<ValType>(vals, greater_than) {}

	void add_item(ValType const& val) override { c_heap<ValType>::add_item(val, greater_than); }

	void add_items(std::vector<ValType> const& vals) override { c_heap<ValType>::add_items(vals, greater_than); }

	void remove_item() { c_heap<ValType>::remove_item(greater_than); }
};