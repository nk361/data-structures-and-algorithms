#pragma once
#include <vector>
#include "c_heap.h"

template <typename ValType, template<class> class NodeType>
class c_min_heap : public c_heap<ValType, NodeType>
{
public:
	//this is the only difference to max heap and the one in the vector param constructor
	bool (*less_than)(ValType const&, ValType const&) { [](ValType const& left, ValType const& right) { return left < right; } };

	c_min_heap() = delete;
	explicit c_min_heap(ValType const& val);
	//must give default param value here of the lambda because otherwise greater_than is not initialized when c_heap's constructor needs it (this also means greater than can be changed with a second param)
	explicit c_min_heap(std::vector<ValType> const& vals, bool(*less_than)(ValType const&, ValType const&) = [](ValType const& left, ValType const& right) { return left < right; });

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item();
};

#include "c_min_heap.inl"