#pragma once
#include <cmath>
#include "c_binary_tree.h"

template <class ValType, template<class> class NodeType, typename Operation>
class c_heap : public c_binary_tree<ValType, NodeType>
{
public:
	int size;

	c_heap() = delete;
	explicit c_heap(ValType const& val);
	explicit c_heap(std::vector<ValType> const& vals);

	//uses c_binary_tree's destructor

	void trickle_up(std::vector<NodeType<ValType> * *> ancstrs) const;
	void trickle_down();

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item();
	
	int static amount_in_level(int const& level);
	int static amount_full_tree(int const& levels);
	int static amount_complete_levels(int const& sz);
	int static amount_last_level(int const& sz);
};

#include "c_heap.inl"