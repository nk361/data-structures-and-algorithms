#pragma once
#include <vector>

template <class ValType, template<class> class NodeType>
class c_tree
{
public:
	NodeType<ValType> * root;

	c_tree() = delete;

	explicit c_tree(ValType const& val);

	virtual void add_item(ValType const& val) = 0;
	virtual void add_items(std::vector<ValType> const& vals) = 0;
	virtual void remove_item(ValType const& val) = 0;

	~c_tree();//not virtual because of unique tree navigation
};

#include "c_tree.inl"