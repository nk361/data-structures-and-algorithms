#pragma once
#include "stdafx.h"
#include "c_node.h"
#include "c_tree.h"

template <class MyType>
class c_binary_tree : public c_tree<MyType>
{
public:
	c_binary_tree() = delete;

	explicit c_binary_tree(MyType const& val) : c_tree(val) {}
	
	virtual void add_item(MyType const& val) override = 0;//needs defined in derived classes for them to decide where to place that type

	virtual void add_items(std::vector<MyType> const& vals) override = 0;//probably just a for each calling their add_item function

	virtual void remove_item(MyType const& val) = 0;

	c_node<MyType> * rotate_left(c_node<MyType> * grandparent)
	{
		c_node<MyType> * temp = grandparent->right;
		grandparent->right = temp->left;
		temp->left = grandparent;
		return temp;//the new grandparent
	}

	c_node<MyType> * rotate_right(c_node<MyType> * grandparent)
	{
		c_node<MyType> * temp = grandparent->left;
		grandparent->left = temp->right;
		temp->right = grandparent;
		return temp;
	}

	c_node<MyType> * rotate_left_right(c_node<MyType> * grandparent)
	{
		grandparent->left = rotate_left(grandparent->left);
		return rotate_right(grandparent);
	}

	c_node<MyType> * rotate_right_left(c_node<MyType> * grandparent)
	{
		grandparent->right = rotate_right(grandparent->right);
		return rotate_left(grandparent);
	}
};
