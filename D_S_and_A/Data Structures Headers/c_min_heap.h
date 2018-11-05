#pragma once
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

template <typename ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(ValType const& val) : c_heap<ValType, NodeType>(val) {}

template <typename ValType, template<class> class NodeType>
c_min_heap<ValType, NodeType>::c_min_heap(std::vector<ValType> const& vals, bool(*less_than)(ValType const&, ValType const&)) : c_heap<ValType, NodeType>(vals, less_than) {}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_item(ValType const& val)
{
	c_heap<ValType, NodeType>::add_item(val, less_than);
}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	c_heap<ValType, NodeType>::add_items(vals, less_than);
}

template <typename ValType, template<class> class NodeType>
void c_min_heap<ValType, NodeType>::remove_item()
{
	c_heap<ValType, NodeType>::remove_item(less_than);
}