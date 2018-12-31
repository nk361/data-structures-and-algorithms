#pragma once
#include <vector>
#include "c_heap.h"

template <class ValType, template<class> class NodeType>
class c_max_heap : public c_heap<ValType, NodeType, std::greater<>>
{
public:
	c_max_heap() = delete;
	explicit c_max_heap(ValType const& val);
	explicit c_max_heap(std::vector<ValType> const& vals);

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item();
};

#include "c_max_heap.inl"