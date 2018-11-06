#pragma once
#include <cmath>
#include "c_binary_tree.h"

template <typename ValType, template<class> class NodeType>
class c_heap : public c_binary_tree<ValType, NodeType>
{
public:
	int size;

	c_heap() = delete;
	explicit c_heap(ValType const& val);
	explicit c_heap(std::vector<ValType> const& vals, bool(*op)(ValType const& left, ValType const& right));

	//uses c_binary_tree's destructor

	void trickle_up(std::vector<NodeType<ValType> * *> ancstrs, bool(*op)(ValType const& left, ValType const& right)) const;
	void trickle_down(bool(*op)(ValType const& left, ValType const& right));

	void add_item(ValType const& val, bool(*op)(ValType const& left, ValType const& right));
	void add_items(std::vector<ValType> const& vals, bool(*op)(ValType const& left, ValType const& right));
	void remove_item(bool(*op)(ValType const& left, ValType const& right));
	
	int static amount_in_level(int const& level);
	int static amount_full_tree(int const& levels);
	int static amount_complete_levels(int const& sz);
	int static amount_last_level(int const& sz);
};

#include "c_heap.inl"