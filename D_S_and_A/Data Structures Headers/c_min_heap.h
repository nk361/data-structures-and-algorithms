#pragma once
#include <vector>
#include "c_heap.h"

template <class ValType, template<class> class NodeType>
class c_min_heap : public c_heap<ValType, NodeType, std::less<>>
{
public:
	c_min_heap() = delete;
	explicit c_min_heap(ValType const& val);
	explicit c_min_heap(std::vector<ValType> const& vals);

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item();
};

#include "c_min_heap.inl"