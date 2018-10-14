#pragma once
#include "c_tree.h"

template <typename  ValType, template<class> class NodeType>
class c_binary_tree : public c_tree<ValType, NodeType>
{
public:
	c_binary_tree() = delete;

	explicit c_binary_tree(ValType const& val) : c_tree(val) {}
	
	/*
	 *This deconstructor uses a pointer to a pointer so that it can navigate items without changing them or change them with *current
	 *It favors navigating left first, right when there is no left child
	 *It pushes the previous node to a vector of pointer to pointers so that it can retrace it's steps back up the tree
	 *After a node is deleted, current it set to the last item on the stack or the parent of that deleted node
	 *Later I may upgrade this deconstructor to handle any amount of children that a single node can have
	 *Because this is an iterative method instead of recursive, there is no stack issue with larger size, only the size of the vector of ancestors
	 *When the tree is properly balanced, ancestors can reach a max length of nlogn, if the tree is not balanced, it can reach a max length of n
	 */
	virtual ~c_binary_tree()
	{
		if (this->root != nullptr)//incase root was all that was left and it got removed
		{
			NodeType<ValType> * * current{ &(this->root) };//made to navigate without changing tree pointer values unless intended
			std::vector<NodeType<ValType> * *> ancestors{ { current } };//using this vector like a stack
			while (true)
			{
				if ((*current)->left != nullptr)
				{
					current = &((*current)->left);
					ancestors.push_back(current);
				}
				else if ((*current)->right != nullptr)
				{
					current = &((*current)->right);
					ancestors.push_back(current);
				}
				if ((*current)->left == nullptr && (*current)->right == nullptr)
				{
					ancestors.pop_back();

					delete *current;
					*current = nullptr;

					if (this->root == nullptr)//tree deleted
						break;

					current = ancestors.back();//go back up one parent
				}
			}
		}
	}

	virtual void add_item(ValType const& val) override {};//needs defined in derived classes for them to decide where to place that type

	virtual void add_items(std::vector<ValType> const& vals) override {};//probably just a for each calling their add_item function

	virtual void remove_item(ValType const& val) override {};//not pure virtual because heaps don't take a param so they don't override this

	NodeType<ValType> * rotate_left(NodeType<ValType> * grandparent)//these only work for nodes that don't have other pointer references to change
	{
		NodeType<ValType> * temp{ grandparent->right };
		grandparent->right = temp->left;
		temp->left = grandparent;
		return temp;//the new grandparent
	}

	NodeType<ValType> * rotate_right(NodeType<ValType> * grandparent)
	{
		NodeType<ValType> * temp{ grandparent->left };
		grandparent->left = temp->right;
		temp->right = grandparent;
		return temp;
	}

	NodeType<ValType> * rotate_left_right(NodeType<ValType> * grandparent)
	{
		grandparent->left = rotate_left(grandparent->left);
		return rotate_right(grandparent);
	}

	NodeType<ValType> * rotate_right_left(NodeType<ValType> * grandparent)
	{
		grandparent->right = rotate_right(grandparent->right);
		return rotate_left(grandparent);
	}
};