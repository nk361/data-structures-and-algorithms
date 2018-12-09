#pragma once
#include <set>

#include "c_linked_list.h"

template <class ValType, template <class> class NodeType>
c_linked_list<ValType, NodeType>::c_linked_list(ValType const& val)
{
	if (head == nullptr)
		head = new NodeType<ValType>{ val, 1 };
	else
	{
		NodeType<ValType> * * current{ &head };
		while (true)
		{
			if ((*current)->children[0] == nullptr)
			{
				(*current)->children[0] = new NodeType<ValType>{ val, 1 };
				break;
			}
			current = &(*current)->children[0];
		}
	}
}

template <class ValType, template <class> class NodeType>
c_linked_list<ValType, NodeType>::c_linked_list(std::vector<ValType> const& vals)
{
	head = new NodeType<ValType>{ vals[0], 1 };
	for (int i{ 1 }; i < vals.size(); ++i)
		c_linked_list<ValType, NodeType>::add_item(vals[i]);
}

template <class ValType, template <class> class NodeType>
c_linked_list<ValType, NodeType>::~c_linked_list()
{
	if (head != nullptr)
		if (head->children[0] == nullptr)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			NodeType<ValType> * * current{ &head->children[0] };
			std::vector<NodeType<ValType> * *> ancestors{ &head };

			while (true)//add pointers to ancestors list
			{
				ancestors.push_back(current);
				if ((*current)->children[0] == nullptr)
					break;
				current = &(*current)->children[0];
			}

			for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//delete all nodes from back to front
			{
				delete *ancestors[i];
				*ancestors[i] = nullptr;
			}
		}
}

template <class ValType, template <class> class NodeType>
NodeType<ValType> * * c_linked_list<ValType, NodeType>::operator[](int index)
{
	NodeType<ValType> * * current{ &head };
	for (int i{ 0 }; i <= index; ++i)//go down each node until you reach that count
	{
		if (i == index)
			return current;

		if ((*current)->children[0] == nullptr)//reached last node before index, index out of range
			break;

		current = &(*current)->children[0];
	}
	throw std::out_of_range{ "c_linked_list [] operator index out of range, index given: " + std::to_string(index) };
}

template <class ValType, template <class> class NodeType>
void c_linked_list<ValType, NodeType>::add_item(ValType const& val)
{
	if (head == nullptr)
		head = new NodeType<ValType>{ val, 1 };
	else
	{
		NodeType<ValType> * * current{ &head };
		while (true)
		{
			if ((*current)->children[0] == nullptr)
			{
				(*current)->children[0] = new NodeType<ValType>{ val, 1 };
				break;
			}
			current = &(*current)->children[0];
		}
	}
}

template <class ValType, template <class> class NodeType>
void c_linked_list<ValType, NodeType>::add_items(ValType const& vals)
{
	for (ValType val : vals)
		c_linked_list<ValType, NodeType>::add_item(val);
}

template <class ValType, template <class> class NodeType>
void c_linked_list<ValType, NodeType>::remove_item(ValType const& val)
{
	if (head->value == val)
		if (head->children[0] != nullptr)
		{
			NodeType<ValType> * * temp_child{ &head->children[0] };//store head's child
			head = (*temp_child);//set head to it's old child
		}
		else
			head = nullptr;
	else//I do head seperately to make use of having the previous node available for other deletions
	{
		NodeType<ValType> * * current{ &head };
		while (true)
		{
			if ((*current)->children[0] == nullptr)//reached end of list
				break;
			if ((*current)->children[0]->value == val)
			{
				NodeType<ValType> * * temp_child{ &(*current)->children[0]->children[0] };//store child's child
				(*current)->children[0] = (*temp_child);//assign child to old node's child
			}
			else
				current = &(*current)->children[0];//navigate down one node
		}
	}
}

template <class ValType, template <class> class NodeType>
void c_linked_list<ValType, NodeType>::remove_item_by_index(int const& index)
{
	if (index == 0)
	{
		NodeType<ValType> * * temp_child{ &head->children[0] };//store head's child
		head = (*temp_child);//set head to it's old child
	}
	else//I do head seperately to make use of having the previous node available for other deletions
	{
		NodeType<ValType> * * temp_parent{ (*this)[index - 1] };//parent - only one index call in O(n)
		NodeType<ValType> * * temp_child{ &(*temp_parent)->children[0]->children[0] };//grandchild
		(*temp_parent)->children[0] = (*temp_child);//parent's child becomes grandchild
	}
}

template <class ValType, template <class> class NodeType>
size_t c_linked_list<ValType, NodeType>::length()
{
	size_t len = 0;
	if (head != nullptr)//no head, len stays 0
	{
		++len;//count head
		NodeType<ValType> * * current{ &head };
		while (true)
			if ((*current)->children[0] != nullptr)//go to next node
			{
				current = &(*current)->children[0];
				++len;//count all other nodes
			}
			else//end of list reached
				break;
	}
	return len;
}

template <class ValType, template <class> class NodeType>
int c_linked_list<ValType, NodeType>::amount_reoccurs(ValType const& val)
{
	int count = 0;
	if (head != nullptr)
	{
		NodeType<ValType> * * current{ &head };
		while (true)
		{
			if ((*current)->value == val)
				++count;
			if ((*current)->children[0] != nullptr)//go to next node
				current = &(*current)->children[0];
			else//end of list reached
				break;
		}
	}
	return count;
}

template <class ValType, template <class> class NodeType>
bool c_linked_list<ValType, NodeType>::detect_loop()
{
	if (head != nullptr)
	{
		NodeType<ValType> * * current{ &head };
		std::set<NodeType<ValType> *> addresses_encountered{ (*current) };//add head
		while (true)
		{
			if ((*current)->children[0] != nullptr)//go to next node
				current = &(*current)->children[0];
			else//end of list reached
				break;
			if (addresses_encountered.find((*current)) != addresses_encountered.end())//node address already encountered
				return true;
		}
	}
	return false;
}

template <class ValType, template <class> class NodeType>
size_t c_linked_list<ValType, NodeType>::length_of_loop()
{
	if (head != nullptr)
	{
		NodeType<ValType> * * current{ &head };
		std::set<NodeType<ValType> *> addresses_encountered{ (*current) };//add head
		typename std::set<NodeType<ValType> *>::iterator first_found;
		while (true)
		{
			if ((*current)->children[0] != nullptr)//go to next node
				current = &(*current)->children[0];
			else//end of list reached
				break;
			first_found = addresses_encountered.find((*current));
			if (first_found != addresses_encountered.end())//node address already encountered
			{
				NodeType<ValType> * * loop_node{ &(*current)->children[0] };//start after current, current must be in loop
				size_t len{ 1 };//start at one counting current
				while (true)
					if ((*current) != (*loop_node))//loop node is in loop and the end isn't found yet
					{
						loop_node = &(*loop_node)->children[0];
						++len;
					}
					else//end of loop/first element repeated found
						return len;
			}
		}
	}
	return 0;
}

//O(n)
//g  p  c
//5->4->3->nullptr
//   g  p  c
//5<-4  3->nullptr
//nullptr<-5<-4<-3
template <class ValType, template <class> class NodeType>
void c_linked_list<ValType, NodeType>::reverse()
{
	if (head != nullptr && head->children[0] != nullptr)//has at least two list elements
	{
		NodeType<ValType> * grandparent{ head };
		NodeType<ValType> * parent{ grandparent->children[0] };//store head's child so grandparent can change
		while (parent != nullptr)
		{
			NodeType<ValType> * child{ parent->children[0] };//not a double pointer to store an address that won't change in the line below
			parent->children[0] = grandparent;//change the direction the middle node/parent points
			grandparent = parent;//move these two down one in the list
			parent = child;
		}
		head->children[0] = nullptr;//make new end of list at old first element
		head = grandparent;//make first element now last element
	}
}