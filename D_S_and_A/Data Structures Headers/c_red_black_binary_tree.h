#pragma once
#include "c_binary_tree.h"

template<typename ValType, template<class> class NodeType>
class c_red_black_binary_tree : public c_binary_tree<ValType, NodeType>
{
public:
	c_red_black_binary_tree() = delete;
	explicit c_red_black_binary_tree(ValType const& val);
	explicit c_red_black_binary_tree(std::vector<ValType> const& vals);

	//using c_binary_tree's virtual destructor, empty braces to prevent default deconstructor from having unwanted code
	~c_red_black_binary_tree() {}

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item(ValType const& val) override;

	void static color_flip(NodeType<ValType> * * grandparent);
	void rebalance(NodeType<ValType> * * grandparent);
};

#include "c_red_black_binary_tree.inl"