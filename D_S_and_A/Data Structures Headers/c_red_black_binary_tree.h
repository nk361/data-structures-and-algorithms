#pragma once
#include "c_binary_tree.h"

template<typename ValType, template<class> class NodeType>
class c_red_black_binary_tree : c_binary_tree<ValType, NodeType>
{
	c_red_black_binary_tree() = delete;
	explicit c_red_black_binary_tree(ValType const& val);
	explicit c_red_black_binary_tree(std::vector<ValType> const& vals);

	void add_item(ValType const& val) override;
	void add_items(std::vector<ValType> const& vals) override;
	void remove_item(ValType const& val) override;

	void rebalance(NodeType<ValType> * * chain_node);
};

template<typename ValType, template<class> class NodeType>
c_red_black_binary_tree<ValType, NodeType>::c_red_black_binary_tree(ValType const& val) : c_binary_tree<ValType, NodeType>(val) {}

template<typename ValType, template<class> class NodeType>
c_red_black_binary_tree<ValType, NodeType>::c_red_black_binary_tree(std::vector<ValType> const& vals) : c_binary_tree<ValType, NodeType>(vals[0])
{
	for (size_t i{ 1 }; i < vals.size(); ++i)
		c_red_black_binary_tree<ValType, NodeType>::add_item(vals[i]);
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::add_item(ValType const& val)
{
	
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::remove_item(ValType const& val)
{
	
}

template<typename ValType, template<class> class NodeType>
void c_red_black_binary_tree<ValType, NodeType>::rebalance(NodeType<ValType> * * grandparent)
{
	
}