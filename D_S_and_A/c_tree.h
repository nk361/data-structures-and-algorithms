#pragma once
#include <vector>

template <typename ValType, template<class> class NodeType>
class c_tree
{
public:
	NodeType<ValType> * root;

	c_tree() = delete;

	explicit c_tree(ValType const& val)
	{
		root = new NodeType<ValType>{ val };
	}

	virtual void add_item(ValType const& val) = 0;
	virtual void add_items(std::vector<ValType> const& vals) = 0;
};
