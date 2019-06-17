#pragma once
#include <vector>

#include "c_tree.h"
#include "Iterators/c_bst_iterator_in_order.h"

template<class DataType, class NodeType = c_poly_node<DataType>, typename Operation = std::less<>>
class c_binary_tree : public c_tree<DataType, NodeType>
{
	NodeType * tail = nullptr;
public:
	c_binary_tree() = delete;
	explicit c_binary_tree(DataType const& val);
	explicit c_binary_tree(std::vector<DataType> const& vals);

	c_binary_tree(c_binary_tree<DataType, NodeType, Operation>& other);//copy constructor
	c_binary_tree<DataType, NodeType, Operation>& operator=(c_binary_tree<DataType, NodeType, Operation>& other);//copy assignment operator

	c_binary_tree(c_binary_tree<DataType, NodeType, Operation>&& other) noexcept;//move constructor
	c_binary_tree<DataType, NodeType, Operation>& operator=(c_binary_tree<DataType, NodeType, Operation>&& other) noexcept;//move assignment operator
	
	~c_binary_tree();//not virtual because of unique tree navigation

	c_bst_iterator_in_order<DataType, NodeType> begin();
	c_bst_iterator_in_order<DataType, NodeType> end();

	virtual void add_item(DataType const& val) override;
	virtual void add_items(std::vector<DataType> const& vals) override;
	void remove_item(DataType const& val) override;//no virtual keyword to show it is not overridden in c_heap

	NodeType * rotate_left(NodeType * grandparent);//these only work for nodes that don't have other pointer references to change other than just grandparent, left, and right
	NodeType * rotate_right(NodeType * grandparent);
	NodeType * rotate_left_right(NodeType * grandparent);
	NodeType * rotate_right_left(NodeType * grandparent);

	NodeType * * find_node(NodeType * * rt, DataType const& val);//take and return pointer to pointer so the node in the tree can be changed
	std::vector<NodeType * *> find_node_with_path(NodeType * * rt, DataType const& val);

	NodeType * * lca(NodeType * * rt, DataType const& val1, DataType const& val2);

	size_t depth(NodeType * rt, DataType const& val);

	/*ValType successor(ValType const& val, std::vector<NodeType<ValType> * *> const& ancestors)
	{
		
	}

	ValType predecessor(ValType const& val, std::vector<NodeType<ValType> * *> const& ancestors)
	{
		
	}*/
};

#include "c_binary_tree.inl"