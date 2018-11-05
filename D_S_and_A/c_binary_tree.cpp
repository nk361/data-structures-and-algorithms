#include "stdafx.h"
#include "Data Structures Headers/c_binary_tree.h"

template <typename ValType, template<class> class NodeType>
c_binary_tree<ValType, NodeType>::c_binary_tree(ValType const& val) : c_tree<ValType, NodeType>(val) {}//explicit is only allowed inside class and other constructor calls don't show in class

template <typename ValType, template<class> class NodeType>
c_binary_tree<ValType, NodeType>::c_binary_tree(std::vector<ValType> const& vals) : c_tree<ValType, NodeType>(vals[0])
{
	for (size_t i{ 1 }; i < vals.size(); ++i)//start at one, send first val off to be root
		c_binary_tree<ValType, NodeType>::add_item(vals[i]);
}

/*
 *This deconstructor uses a pointer to a pointer so that it can navigate items without changing them or change them with *current
 *It favors navigating left first, right when there is no left child
 *It pushes the previous node to a vector of pointer to pointers so that it can retrace it's steps back up the tree
 *After a node is deleted, current it set to the last item on the stack or the parent of that deleted node
 *Later I may upgrade this deconstructor to handle any amount of children that a single node can have
 *Because this is an iterative method instead of recursive, there is no stack issue with larger size, only the size of the vector of ancestors
 *When the tree is properly balanced, ancestors can reach a max length of nlogn, if the tree is not balanced, it can reach a max length of n
 */
template <typename ValType, template<class> class NodeType>
c_binary_tree<ValType, NodeType>::~c_binary_tree()//not virtual because of unique tree navigation
{
	if (c_tree<ValType, NodeType>::root != nullptr)//incase root was all that was left and it was removed
	{
		NodeType<ValType> * * current{ &(c_tree<ValType, NodeType>::root) };//made to navigate without changing tree pointer values unless intended
		std::vector<NodeType<ValType> * *> ancestors{ { current } };//using this vector like a stack
		while (true)
		{
			if ((*current)->children[0] != nullptr)
			{
				current = &((*current)->children[0]);
				ancestors.push_back(current);
			}
			else if ((*current)->children[1] != nullptr)
			{
				current = &((*current)->children[1]);
				ancestors.push_back(current);
			}
			if ((*current)->children[0] == nullptr && (*current)->children[1] == nullptr)
			{
				ancestors.pop_back();

				delete *current;
				*current = nullptr;

				if (c_tree<ValType, NodeType>::root == nullptr)//tree deleted
					break;

				current = ancestors.back();//go back up one parent
			}
		}
	}
}

template <typename ValType, template<class> class NodeType>
void c_binary_tree<ValType, NodeType>::add_item(ValType const& val)
{
	NodeType<ValType> * current{ c_tree<ValType, NodeType>::root };
	while (true)
		if (val < current->value)
		{
			if (current->children[0] == nullptr)
			{
				current->children[0] = new NodeType<ValType>{ val, 2 };
				break;
			}
			current = current->children[0];
		}
		else//greater than or equal to
		{
			if (current->children[1] == nullptr)
			{
				current->children[1] = new NodeType<ValType>{ val, 2 };
				break;
			}
			current = current->children[1];
		}
}

template <typename ValType, template<class> class NodeType>
void c_binary_tree<ValType, NodeType>::add_items(std::vector<ValType> const& vals)
{
	for (ValType val : vals)
		c_binary_tree<ValType, NodeType>::add_item(val);
}

template <typename ValType, template<class> class NodeType>
void c_binary_tree<ValType, NodeType>::remove_item(ValType const& val)
{
	NodeType<ValType> * * found{ find_node(&(c_tree<ValType, NodeType>::root), val) };

	if (*found != nullptr)
		if ((*found)->children[0] == nullptr && (*found)->children[1] == nullptr)
		{
			delete *found;
			*found = nullptr;
		}
		else if ((*found)->children[1] == nullptr)
			*found = (*found)->children[0];
		else if ((*found)->children[0] == nullptr)
			*found = (*found)->children[1];
		else//both child nodes exist
		{
			NodeType<ValType> * * current{ &(*found)->children[1] };//search for the leftmost node of right child
			while (true)
				if ((*current)->children[0] != nullptr)
					current = &(*current)->children[0];
				else
					break;
			(*found)->value = (*current)->value;//swap with next largest in tree

			if ((*current)->children[1] == nullptr)//delete node if all the way left
			{
				delete *current;
				*current = nullptr;
			}
			else//move right nodes up if it was purely the right node
				*current = (*current)->children[1];
		}
}

//these only work for nodes that don't have other pointer references to change other than just grandparent, left, and right
template <typename ValType, template<class> class NodeType>
NodeType<ValType> * c_binary_tree<ValType, NodeType>::rotate_left(NodeType<ValType> * grandparent)
{
	NodeType<ValType> * temp{ grandparent->children[1] };//store grandparent's right child
	grandparent->children[1] = temp->children[0];//put right's left child as grandparent's right
	temp->children[0] = grandparent;//put old grandparent as grandparent's right child's left child
	return temp;//the new grandparent for the old to be assigned to
}

template <typename ValType, template<class> class NodeType>
NodeType<ValType> * c_binary_tree<ValType, NodeType>::rotate_right(NodeType<ValType> * grandparent)
{
	NodeType<ValType> * temp{ grandparent->children[0] };
	grandparent->children[0] = temp->children[1];
	temp->children[1] = grandparent;
	return temp;
}

template <typename ValType, template<class> class NodeType>
NodeType<ValType> * c_binary_tree<ValType, NodeType>::rotate_left_right(NodeType<ValType> * grandparent)
{
	grandparent->children[0] = rotate_left(grandparent->children[0]);//perform left rotate on grandparent's left child
	return rotate_right(grandparent);//return the new grandparent after right rotate on grandparent
}

template <typename ValType, template<class> class NodeType>
NodeType<ValType> * c_binary_tree<ValType, NodeType>::rotate_right_left(NodeType<ValType> * grandparent)
{
	grandparent->children[1] = rotate_right(grandparent->children[1]);
	return rotate_left(grandparent);
}

template <typename ValType, template<class> class NodeType>
NodeType<ValType> * * c_binary_tree<ValType, NodeType>::find_node(NodeType<ValType> * * rt, ValType const& val)//take and return pointer to pointer so the node in the tree can be changed
{
	NodeType<ValType> * * current{ rt };
	while (true)
	{
		if ((*current)->value == val)
			return current;
		if (val < (*current)->value)
		{
			if ((*current)->children[0] == nullptr)
				return &(*current)->children[0];//returning a reference to a pointer holding nullptr
			current = &(*current)->children[0];
		}
		else
		{
			if ((*current)->children[1] == nullptr)
				return &(*current)->children[1];//returning a reference to a pointer holding nullptr
			current = &(*current)->children[1];
		}
	}
}

//This function works the same as find_node, except it keeps track of ancestors along the way
//It returns a vector with pointers to pointers of the ancestors with the last element being the found node
template <typename ValType, template<class> class NodeType>
std::vector<NodeType<ValType> * *> c_binary_tree<ValType, NodeType>::find_node_with_path(NodeType<ValType> * * rt, ValType const& val)
{
	NodeType<ValType> * * current{ rt };
	std::vector<NodeType<ValType> * *> ancestors{ rt };
	while (true)
	{
		if ((*current)->value == val)
			return ancestors;
		if (val < (*current)->value)
		{
			if ((*current)->children[0] == nullptr)
				return {};//returning an empty list
			current = &(*current)->children[0];
		}
		else
		{
			if ((*current)->children[1] == nullptr)
				return {};
			current = &(*current)->children[1];
		}
		ancestors.push_back(current);
	}
}

//Lowest common ancestor node
//This function takes the current root by reference and two values
//It loops through looking for the FIRST node that would make the two values split paths in the tree
//If one or both values could not be located in the tree, this returns a pointer to nullptr
//It returns a pointer to the lca node so that it can be changed
template <typename ValType, template<class> class NodeType>
NodeType<ValType> * * c_binary_tree<ValType, NodeType>::lca(NodeType<ValType> * * rt, ValType const& val1, ValType const& val2)
{
	NodeType<ValType> * * current{ rt };
	if ((*find_node(rt, val1) != nullptr) && (*find_node(rt, val2)) != nullptr)
		while (true)
			if (val1 < (*current)->value && val2 < (*current)->value)
				current = &(*current)->children[0];
			else if (val1 > (*current)->value && val2 > (*current)->value)
				current = &(*current)->children[1];
			else
				return current;
	return *find_node(rt, val1) == nullptr ? find_node(rt, val1) : find_node(rt, val2);//return pointer to nullptr, would like a better way
}

template <typename ValType, template<class> class NodeType>
size_t c_binary_tree<ValType, NodeType>::depth(NodeType<ValType> * rt, ValType const& val)
{
	int count{ 1 };
	NodeType<ValType> * current{ rt };
	while (true)
	{
		if (current->value == val)
			return count;
		if (val < current->value)
			current = current->children[0];
		else
			current = current->children[1];
		++count;
	}
}