#pragma once
#include "c_binary_tree.h"

template<class ValType, template<class> class NodeType>
class c_avl_binary_tree : public c_binary_tree<ValType, NodeType>
{
public:
	c_avl_binary_tree() = delete;
	explicit c_avl_binary_tree(ValType const& val);
	explicit c_avl_binary_tree(std::vector<ValType> const& vals);

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item(ValType const& val) override;

	size_t height(NodeType<ValType> * r_avl_node);
	void rebalance(NodeType<ValType> * * chain_node);//call this with a reference to the grandparent
};

#include "c_avl_binary_tree.inl"