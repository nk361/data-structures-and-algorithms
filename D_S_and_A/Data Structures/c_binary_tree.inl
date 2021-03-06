#pragma once

#include <vector>

#include "c_binary_tree.h"

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>::c_binary_tree(DataType const& val) : c_tree<DataType, NodeType>(val) {}//explicit is only allowed inside class and other constructor calls don't show in class

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>::c_binary_tree(std::vector<DataType> const& vals) : c_tree<DataType, NodeType>(vals[0])
{
	for (size_t i{ 1 }; i < vals.size(); ++i)//start at one, send first val off to be root
		c_binary_tree<DataType, NodeType, Operation>::add_item(vals[i]);
}

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>::c_binary_tree(c_binary_tree<DataType, NodeType, Operation>& other)//copy constructor
{
	*this = other;//reuse copy code in copy assignment operator
}

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>& c_binary_tree<DataType, NodeType, Operation>::operator=(c_binary_tree<DataType, NodeType, Operation>& other)//copy assignment operator
{
	if (this != &other)
	{
		this->~c_binary_tree();//free nodes

		//perform copy
		//algorithm for level order traversal or breadth first search, may be replaced by an iterator, not sure how to make separate begin and end functions
		//to be sure all items have the exact same position in the tree as other
		if(other.root != nullptr)
		{
			std::vector<NodeType *> unvisited{ other.root };//max size that this gets is the largest level + the first two children, this vector is used like a queue
			while (!unvisited.empty())
			{
				if(unvisited[0]->children[0] != nullptr)//has a left child
					unvisited.push_back(unvisited[0]->children[0]);
				if(unvisited[0]->children[1] != nullptr)//has a right child
					unvisited.push_back(unvisited[0]->children[1]);

				c_binary_tree<DataType, NodeType, Operation>::add_item(unvisited[0]->value);//add value to current tree
				unvisited.erase(unvisited.begin());//remove first item in unvisited
			}
		}
	}
	return *this;
}

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>::c_binary_tree(c_binary_tree<DataType, NodeType, Operation>&& other) noexcept//move constructor
{
	*this = other;//reuse move code in copy assignment operator
}

template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>& c_binary_tree<DataType, NodeType, Operation>::operator=(c_binary_tree<DataType, NodeType, Operation>&& other) noexcept//move assignment operator
{
	if(this != &other)
	{
		//perform move
		c_binary_tree<DataType, NodeType, Operation>::root = other.root;
		tail = other.tail;
		other.root = nullptr;
		other.tail = nullptr;
	}
	return *this;
}

/*
 *This destructor uses a pointer to a pointer so that it can navigate items without changing them or change them with *current
 *It favors navigating left first, right when there is no left child
 *It pushes the previous node to a vector of pointer to pointers so that it can retrace it's steps back up the tree
 *After a node is deleted, current it set to the last item on the stack or the parent of that deleted node
 *Later I may upgrade this destructor to handle any amount of children that a single node can have
 *Because this is an iterative method instead of recursive, there is no stack issue with larger size, only the size of the vector of ancestors
 *When the tree is properly balanced, ancestors can reach a max length of nlogn, if the tree is not balanced, it can reach a max length of n
 */
template<class DataType, class NodeType, typename Operation>
c_binary_tree<DataType, NodeType, Operation>::~c_binary_tree()//not virtual because of unique tree navigation
{
	if (c_tree<DataType, NodeType>::root != nullptr)//incase root was all that was left and it was removed
	{
		NodeType * * current{ &(c_tree<DataType, NodeType>::root) };//made to navigate without changing tree pointer values unless intended
		std::vector<NodeType * *> ancestors{ { current } };//using this vector like a stack
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

				if (c_tree<DataType, NodeType>::root == nullptr)//tree deleted
					break;

				current = ancestors.back();//go back up one parent
			}
		}
	}
}

template<class DataType, class NodeType, typename Operation>
c_bst_iterator_in_order<DataType, NodeType> c_binary_tree<DataType, NodeType, Operation>::begin()
{
	return c_bst_iterator_in_order<DataType, NodeType>{ &(c_binary_tree<DataType, NodeType, Operation>::root) };
}

//this function finds the end of the tree by using ONLY right nodes similar to a linked list to find the rightmost node (good for only in order traversal)
template<class DataType, class NodeType, typename Operation>
c_bst_iterator_in_order<DataType, NodeType> c_binary_tree<DataType, NodeType, Operation>::end()
{
	if (tail == nullptr)
		tail = c_binary_tree<DataType, NodeType, Operation>::root;

	while (tail->children[1] != nullptr)
		tail = tail->children[1];

	return c_bst_iterator_in_order<DataType, NodeType>{ &tail->children[1] };
}

template<class DataType, class NodeType, typename Operation>
void c_binary_tree<DataType, NodeType, Operation>::add_item(DataType const& val)
{
	if (c_binary_tree<DataType, NodeType, Operation>::root == nullptr)//incase there is no root
		c_binary_tree<DataType, NodeType, Operation>::root = new NodeType{ val, 2 };
	else
	{
		Operation const op = Operation();

		NodeType * current{ c_binary_tree<DataType, NodeType, Operation>::root };
		while (true)
			if (op(val, current->value))
			{
				if (current->children[0] == nullptr)
				{
					current->children[0] = new NodeType{ val, 2 };
					break;
				}
				current = current->children[0];
			}
			else//greater than or equal to
			{
				if (current->children[1] == nullptr)
				{
					current->children[1] = new NodeType{ val, 2 };
					break;
				}
				current = current->children[1];
			}
	}
	
}

template<class DataType, class NodeType, typename Operation>
void c_binary_tree<DataType, NodeType, Operation>::add_items(std::vector<DataType> const& vals)
{
	for (DataType val : vals)
		c_binary_tree<DataType, NodeType, Operation>::add_item(val);
}

template<class DataType, class NodeType, typename Operation>
void c_binary_tree<DataType, NodeType, Operation>::remove_item(DataType const& val)
{
	NodeType * * found{ c_binary_tree<DataType, NodeType, Operation>::find_node(&(c_binary_tree<DataType, NodeType, Operation>::root), val) };

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
			NodeType * * current{ &(*found)->children[1] };//search for the leftmost node of right child
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

//these only work for nodes that don't have other pointer references to change other than just left and right
template<class DataType, class NodeType, typename Operation>
NodeType * c_binary_tree<DataType, NodeType, Operation>::rotate_left(NodeType * grandparent)
{
	if (tail == grandparent)//to prevent sending an outdated tail to the left side which would make it look for a new tail there when end() is called
		tail = grandparent->children[1]->children[1];

	NodeType * temp{ grandparent->children[1] };//store grandparent's right child
	grandparent->children[1] = temp->children[0];//put right's left child as grandparent's right
	temp->children[0] = grandparent;//put old grandparent as grandparent's right child's left child
	return temp;//the new grandparent for the old to be assigned to
}

//these only work for nodes that don't have other pointer references to change other than just left and right
template<class DataType, class NodeType, typename Operation>
NodeType * c_binary_tree<DataType, NodeType, Operation>::rotate_right(NodeType * grandparent)
{
	NodeType * temp{ grandparent->children[0] };
	grandparent->children[0] = temp->children[1];
	temp->children[1] = grandparent;
	return temp;
}

//these only work for nodes that don't have other pointer references to change other than just left and right
template<class DataType, class NodeType, typename Operation>
NodeType * c_binary_tree<DataType, NodeType, Operation>::rotate_left_right(NodeType * grandparent)
{
	grandparent->children[0] = rotate_left(grandparent->children[0]);//perform left rotate on grandparent's left child
	return rotate_right(grandparent);//return the new grandparent after right rotate on grandparent
}

//these only work for nodes that don't have other pointer references to change other than just left and right
template<class DataType, class NodeType, typename Operation>
NodeType * c_binary_tree<DataType, NodeType, Operation>::rotate_right_left(NodeType * grandparent)
{
	if (tail == grandparent)//to prevent sending an outdated tail to the left side which would make it look for a new tail there when end() is called
		tail = grandparent->children[1];

	grandparent->children[1] = rotate_right(grandparent->children[1]);
	return rotate_left(grandparent);
}

template<class DataType, class NodeType, typename Operation>
NodeType * * c_binary_tree<DataType, NodeType, Operation>::find_node(NodeType * * rt, DataType const& val)//take and return pointer to pointer so the node in the tree can be changed
{
	Operation const op = Operation();

	NodeType * * current{ rt };
	while (true)
	{
		if ((*current)->value == val)
			return current;
		if (op(val, (*current)->value))
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
template<class DataType, class NodeType, typename Operation>
std::vector<NodeType * *> c_binary_tree<DataType, NodeType, Operation>::find_node_with_path(NodeType * * rt, DataType const& val)
{
	Operation const op = Operation();

	NodeType * * current{ rt };
	std::vector<NodeType * *> ancestors{ rt };
	while (true)
	{
		if ((*current)->value == val)
			return ancestors;
		if (op(val, (*current)->value))
		{
			if ((*current)->children[0] == nullptr)
				return {};//returning an empty list
			current = &(*current)->children[0];
		}
		else
		{
			if ((*current)->children[1] == nullptr)
				return {};//returning an empty list
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
template<class DataType, class NodeType, typename Operation>
NodeType * * c_binary_tree<DataType, NodeType, Operation>::lca(NodeType * * rt, DataType const& val1, DataType const& val2)
{
	Operation const op = Operation();

	NodeType * * current{ rt };
	if ((*find_node(rt, val1) != nullptr) && (*find_node(rt, val2)) != nullptr)
		while (true)
			if (op(val1, (*current)->value) && op(val2, (*current)->value))
				current = &(*current)->children[0];
			else if (!op(val1, (*current)->value) && !op(val2, (*current)->value))
				current = &(*current)->children[1];
			else
				return current;
	return *find_node(rt, val1) == nullptr ? find_node(rt, val1) : find_node(rt, val2);//return pointer to nullptr, would like a better way
}

template<class DataType, class NodeType, typename Operation>
size_t c_binary_tree<DataType, NodeType, Operation>::depth(NodeType * rt, DataType const& val)
{
	Operation const op = Operation();

	int count{ 1 };
	NodeType * current{ rt };
	while (true)
	{
		if (current->value == val)
			return count;
		if (op(val, current->value))
			current = current->children[0];
		else
			current = current->children[1];
		++count;
	}
}