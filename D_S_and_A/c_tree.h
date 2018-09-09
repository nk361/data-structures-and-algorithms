#pragma once
#include "c_node.h"
#include <vector>

template <class MyType>
class c_tree
{
public:
	c_node<MyType> * root;

	c_tree() = delete;

	explicit c_tree(MyType const& val)
	{
		root = new c_node<MyType>{ val };
	}

	/*
	 *This deconstructor uses a pointer to a pointer so that it can navigate items without changing them or change them with *current
	 *It favors navigating left first, right when there is no left child
	 *It pushes the previous node to a vector of pointer to pointers so that it can retrace it's steps back up the tree
	 *After a node is deleted, current it set to the last item on the stack or the parent of that deleted node
	 *Later I may upgrade this deconstructor to handle any amount of children that a single node can have
	 *Because this is an iterative method instead of recursive, there is no stack issue with larger size, only the size of the vector of ancestors
	 */
	~c_tree()
	{
		c_node<MyType> * * current = &root;
		std::vector<c_node<MyType> * *> ancestors = { current };//using this vector like a stack
		while(true)
		{
			//std::cout << "Currently on: " << (*current)->value << std::endl;

			if((*current)->left != nullptr)
			{
				//std::cout << "Going left" << std::endl;

				current = &((*current)->left);
				ancestors.push_back(current);
			}
			else if((*current)->right != nullptr)
			{
				//std::cout << "Going right" << std::endl;
				
				current = &((*current)->right);
				ancestors.push_back(current);
			}
			if((*current)->left == nullptr && (*current)->right == nullptr)
			{
				//std::cout << "Deleting: " << (*current)->value << std::endl;

				ancestors.pop_back();

				delete (*current);
				(*current) = nullptr;

				if(root == nullptr)
				{
					//std::cout << "Tree deleted" << std::endl;
					break;
				}

				current = ancestors.back();
			}
		}
	}

	virtual void add_item(MyType const& val) = 0;
	virtual void add_items(std::vector<MyType> const& vals) = 0;
};
