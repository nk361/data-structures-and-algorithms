#pragma once
#include "c_binary_tree.h"
#include "c_AVL_node.h"

template<typename  ValType, template<class> class NodeType>
class c_AVL_binary_tree : public c_binary_tree<ValType, NodeType>//maybe should always be c_AVL_node only
{
public:
	c_AVL_binary_tree() = delete;

	explicit c_AVL_binary_tree(ValType const& val) : c_binary_tree(val) {}

	virtual void add_item(ValType const& val) override = 0;

	virtual void add_items(std::vector<ValType> const& vals) override = 0;

	void remove_item(ValType const& val) override = 0;

	size_t height(c_AVL_node<ValType> * r_avl_node)
	{
		size_t max_height = 1;
		c_AVL_node<ValType> * current{ r_avl_node };
		std::vector<std::pair<c_AVL_node<ValType> *, bool>> ancestors;//store the previous nodes and the direction it went from it
		ancestors.push_back({ current, current->left != nullptr ? true : false });//true shows it went left, false shows it went right
		while (true)
		{
			if (current->left == nullptr && current->right == nullptr)//do this first incase the bool says go right, but there's nothing right either
			{
				if (ancestors.size() > max_height)//check for new record height
					max_height = ancestors.size();

				ancestors.pop_back();//you know the current node is a leaf node, so you can pop it with no worries

				for (size_t i = ancestors.size() - 1; true; --i)//loop to look for the next path or exit if reached the end
				{
					if (ancestors.size() == 0)
						return max_height;

					if (ancestors[i].second && ancestors[i].first->right != nullptr)//found an ancestor with an unexplored right node
					{
						ancestors[i].second = false;
						current = ancestors[i].first;
						break;
					}
					ancestors.pop_back();
				}
			}

			if (ancestors.back().second)//go left
				current = current->left;
			else//go right
				current = current->right;

			ancestors.push_back({ current, current->left != nullptr ? true : false });//this after checks because of initial value
		}
	}
};