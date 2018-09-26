#pragma once
#include "c_binary_tree.h"
#include "c_AVL_node.h"

template <typename  ValType, template<class> class NodeType>
class c_AVL_binary_tree : public c_binary_tree<ValType, NodeType>
{
public:
	c_AVL_binary_tree() = delete;

	explicit c_AVL_binary_tree(ValType const& val) : c_binary_tree(val) {}

	void add_item(ValType const& val) override = 0;

	void add_items(std::vector<ValType> const& vals) override = 0;

	void remove_item(ValType const& val) override = 0;

	size_t height(c_AVL_node<ValType>& r_avl_node)
	{
		size_t max_height = 0;
		if(r_avl_node != nullptr)
		{
			c_AVL_node<ValType> * current = r_avl_node;
			std::vector<c_AVL_node<ValType> *> ancestors;
			while(true)
			{
				//I need to add nodes to the ancestors and compare the longest lengths once nullptr is reached
				//The biggest problem I see at the moment is knowing how to navigate, using the ancestors idea
				//needs a bit more, I was originally using it because the descrutor does, but the destrcutor knows where to navigate
				//because options for navigation are removed over time
				//with the height, I'm not removing any nodes at all
				//I may need to store the direction I've gone? if gone left is true, attempt to go right?
				//Use a list of booleans and that's all I really need to know is if I've gone left there before or not
				//Once I go back one node, I can ditch the booleans for what was below it, which if I do it right
				//I should only have to remove one boolean from the end of the list
				//add a boolean and node to ancestors when going onto a node and remove a node and boolean when backing up onto ancestors
			}
		}
	}

	c_AVL_node<ValType> * rotate_left(c_AVL_node<ValType> * grandparent)//these only work for c_AVL_node nodes, need to change parents
	{
		c_AVL_node<ValType> * temp = grandparent->right;
		grandparent->right = temp->left;
		//grandparent->parent = temp;
		temp->left = grandparent;
		return temp;//the new grandparent
	}

	c_AVL_node<ValType> * rotate_right(c_AVL_node<ValType> * grandparent)
	{
		c_AVL_node<ValType> * temp = grandparent->left;
		grandparent->left = temp->right;
		temp->right = grandparent;
		return temp;
	}

	c_AVL_node<ValType> * rotate_left_right(c_AVL_node<ValType> * grandparent)
	{
		grandparent->left = rotate_left(grandparent->left);
		return rotate_right(grandparent);
	}

	c_AVL_node<ValType> * rotate_right_left(c_AVL_node<ValType> * grandparent)
	{
		grandparent->right = rotate_right(grandparent->right);
		return rotate_left(grandparent);
	}
};
