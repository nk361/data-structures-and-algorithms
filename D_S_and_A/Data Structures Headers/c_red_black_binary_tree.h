#pragma once
#include "c_binary_tree.h"

template<class DataType, class NodeType = c_red_black_poly_node<DataType>, typename Operation = std::less<>>
class c_red_black_binary_tree : public c_binary_tree<DataType, NodeType, Operation>
{
public:
	c_red_black_binary_tree() = delete;
	explicit c_red_black_binary_tree(DataType const& val);
	explicit c_red_black_binary_tree(std::vector<DataType> const& vals);

	//using c_binary_tree's virtual destructor, empty braces to prevent default deconstructor from having unwanted code
	~c_red_black_binary_tree() {}

	void add_item(DataType const& val) override;
	void add_items(std::vector<DataType> const& vals) override;
	void remove_item(DataType const& val) override;

	void static color_flip(NodeType * * grandparent);
	void rebalance(NodeType * * grandparent);
};

#include "c_red_black_binary_tree.inl"