#pragma once
#include <vector>

#include "c_tree.h"
#include "Iterators/c_bst_iterator_in_order.h"

template <class ValType, template<class> class NodeType, typename Operation = std::less<>>
class c_binary_tree : public c_tree<ValType, NodeType>
{
	NodeType<ValType> * tail = nullptr;
public:
	c_binary_tree() = delete;
	explicit c_binary_tree(ValType const& val);
	explicit c_binary_tree(std::vector<ValType> const& vals);

	c_binary_tree(c_binary_tree<ValType, NodeType, Operation>& other);//copy constructor
	c_binary_tree<ValType, NodeType, Operation>& operator=(c_binary_tree<ValType, NodeType, Operation>& other);//copy assignment operator

	c_binary_tree(c_binary_tree<ValType, NodeType, Operation>&& other) noexcept;//move constructor
	c_binary_tree<ValType, NodeType, Operation>& operator=(c_binary_tree<ValType, NodeType, Operation>&& other) noexcept;//move assignment operator
	
	~c_binary_tree();//not virtual because of unique tree navigation

	c_bst_iterator_in_order<ValType, NodeType> begin();
	c_bst_iterator_in_order<ValType, NodeType> end();

	virtual void add_item(ValType const& val) override;
	virtual void add_items(std::vector<ValType> const& vals) override;
	void remove_item(ValType const& val) override;//no virtual keyword to show it is not overridden in c_heap

	NodeType<ValType> * rotate_left(NodeType<ValType> * grandparent);//these only work for nodes that don't have other pointer references to change other than just grandparent, left, and right
	NodeType<ValType> * rotate_right(NodeType<ValType> * grandparent);
	NodeType<ValType> * rotate_left_right(NodeType<ValType> * grandparent);
	NodeType<ValType> * rotate_right_left(NodeType<ValType> * grandparent);

	NodeType<ValType> * * find_node(NodeType<ValType> * * rt, ValType const& val);//take and return pointer to pointer so the node in the tree can be changed
	std::vector<NodeType<ValType> * *> find_node_with_path(NodeType<ValType> * * rt, ValType const& val);

	NodeType<ValType> * * lca(NodeType<ValType> * * rt, ValType const& val1, ValType const& val2);

	size_t depth(NodeType<ValType> * rt, ValType const& val);

	/*ValType successor(ValType const& val, std::vector<NodeType<ValType> * *> const& ancestors)
	{
		
	}

	ValType predecessor(ValType const& val, std::vector<NodeType<ValType> * *> const& ancestors)
	{
		
	}*/
};

#include "c_binary_tree.inl"