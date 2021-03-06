#pragma once

#include <set>
#include <vector>

#include "c_linked_list.h"

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>::c_linked_list(DataType const& data)
{
	head = new NodeType{ data, 1 };
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>::c_linked_list(std::vector<DataType> const& data_list)
{
	head = new NodeType{ data_list[0], 1 };
	for (int i{ 1 }; i < data_list.size(); ++i)
		c_linked_list<DataType, NodeType>::add_item(data_list[i]);
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>::c_linked_list(c_linked_list<DataType, NodeType>& other)//copy constructor, pass by reference to avoid infinite copy
{
	*this = other;//reuse copy code in copy assignment operator
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>& c_linked_list<DataType, NodeType>::operator=(c_linked_list<DataType, NodeType>& other)//copy assignment operator
{
	if (this != &other)//check for self assignment
	{
		this->~c_linked_list();//free nodes
		//be careful of out of memory exceptions since you want these structures to be fine when huge

		//perform copy
		c_linked_list_iterator<DataType, NodeType> current_iter{ &head }, other_iter{ other.begin() };
		while (other_iter != other.end())//this only works because the iterator goes to the nullptr spot at the end of the new list, bst iterator doesn't work like that
		{
			(**current_iter) = new NodeType{ (**other_iter)->value, static_cast<int>((**other_iter)->children.size()) };//size instead of 1 incase future implementations need more and so that the code is similar in other copy constructors without magic numbers
			++current_iter;
			++other_iter;
		}

		tail = (**current_iter);//set tail while you have it instead of having to recalculate
	}
	return *this;
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>::c_linked_list(c_linked_list<DataType, NodeType>&& other) noexcept//move constructor
{
	*this = other;//reuse move code in move assignment operator
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>& c_linked_list<DataType, NodeType>::operator=(c_linked_list<DataType, NodeType>&& other) noexcept//move assignment operator
{
	if (this != &other)//check for self assignment
	{
		//perform move
		head = other.head;
		tail = other.tail;
		other.head = nullptr;
		other.tail = nullptr;
	}
	return *this;
}

template<class DataType, class NodeType>
c_linked_list<DataType, NodeType>::~c_linked_list()
{
	if (head != nullptr)
		if (head->children[0] == nullptr)
		{
			delete head;
			head = nullptr;
		}
		else
		{
			std::vector<NodeType * *> ancestors;
			for(NodeType * * current : *this)
				ancestors.push_back(current);

			for (int i{ static_cast<int>(ancestors.size()) - 1 }; i >= 0; --i)//delete all nodes from back to front to avoid navigating on deleted children pointers
			{
				delete *ancestors[i];
				*ancestors[i] = nullptr;
			}
		}
}

template<class DataType, class NodeType>
NodeType * * c_linked_list<DataType, NodeType>::operator[](int const& index)
{
	NodeType * * current{ &head };
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

template<class DataType, class NodeType>
c_linked_list_iterator<DataType, NodeType> c_linked_list<DataType, NodeType>::begin()
{
	return c_linked_list_iterator<DataType, NodeType>{ &head };
}

template<class DataType, class NodeType>
c_linked_list_iterator<DataType, NodeType> c_linked_list<DataType, NodeType>::end()//worst case is O(n) when first called, after the first call it changes to O(1)
{
	if (tail == nullptr)//first time end has ever been called, so tell it where to start
		tail = head;

	if (tail != nullptr)//check for null incase the end node was deleted
		while (tail->children[0] != nullptr)//navigate down the list looking for the end
			tail = tail->children[0];

	return c_linked_list_iterator<DataType, NodeType>{ &tail->children[0] };
}

template<class DataType, class NodeType>
void c_linked_list<DataType, NodeType>::add_item(DataType const& data)
{
	if (head == nullptr)
		head = new NodeType{ data, 1 };
	else
		*(*this->end()) = new NodeType{ data, 1 };//get the last node and create it's child with val
}

template<class DataType, class NodeType>
void c_linked_list<DataType, NodeType>::add_items(std::vector<DataType> const& data_list)
{
	for (DataType data : data_list)
		c_linked_list<DataType, NodeType>::add_item(data);
}

template<class DataType, class NodeType>
void c_linked_list<DataType, NodeType>::remove_item(DataType const& data)
{
	if (head->value == data)
		if (head->children[0] != nullptr)
		{
			NodeType * * temp_child{ &head->children[0] };//store head's child
			head = (*temp_child);//set head to it's old child
		}
		else
			head = nullptr;
	else//I do head separately to make use of having the previous node available for other deletions
		for (NodeType * * current : *this)
			if ((*current)->value == data)
				(*current) = (*current)->children[0];
}

template<class DataType, class NodeType>
void c_linked_list<DataType, NodeType>::remove_item_by_index(int const& index)
{
	if (index == 0)
	{
		NodeType * * temp_child{ &head->children[0] };//store head's child
		head = (*temp_child);//set head to it's old child
	}
	else//I do head separately to make use of having the previous node available for other deletions
	{
		NodeType * * temp_parent{ (*this)[index - 1] };//parent - only one index call in O(n)
		NodeType * * temp_child{ &(*temp_parent)->children[0]->children[0] };//grandchild
		(*temp_parent)->children[0] = (*temp_child);//parent's child becomes grandchild
	}
}

template<class DataType, class NodeType>
size_t c_linked_list<DataType, NodeType>::length()
{
	size_t len = 0;
	if (head != nullptr)//no head, len stays 0
		for(NodeType * * current : *this)
			++len;
	return len;
}

template<class DataType, class NodeType>
int c_linked_list<DataType, NodeType>::amount_reoccurs(DataType const& data)
{
	int count = 0;
	if (head != nullptr)
		for(NodeType * * current : *this)
			if ((*current)->value == data)
				++count;
	return count;
}

template<class DataType, class NodeType>
bool c_linked_list<DataType, NodeType>::detect_loop()//can't use a for each loop when the linked list may be a loop, end() becomes an infinite loop
{
	if (head != nullptr)
	{	
		NodeType * * current{ &head };
		std::set<NodeType *> addresses_encountered;//add head
		while (true)
		{
			if ((*current)->children[0] != nullptr)//go to next node
				current = &(*current)->children[0];
			else//end of list reached
				break;

			if (addresses_encountered.find((*current)) != addresses_encountered.end())//node address already encountered
				return true;

			addresses_encountered.insert((*current));//add this node to what's been encountered
		}
	}
	return false;
}

template<class DataType, class NodeType>
size_t c_linked_list<DataType, NodeType>::length_of_loop()//can't use a for each loop when the linked list may be a loop, end() becomes an infinite loop
{
	if (head != nullptr)
	{
		NodeType * * current{ &head };
		std::set<NodeType *> addresses_encountered;//add head
		typename std::set<NodeType *>::iterator first_found;
		while (true)
		{
			if ((*current)->children[0] != nullptr)//go to next node
				current = &(*current)->children[0];
			else//end of list reached
				break;
			first_found = addresses_encountered.find((*current));
			if (first_found != addresses_encountered.end())//node address already encountered
			{
				NodeType * * loop_node{ &(*current)->children[0] };//start after current, current must be in loop
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
			addresses_encountered.insert((*current));//add this node to what's been encountered
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
template<class DataType, class NodeType>
void c_linked_list<DataType, NodeType>::reverse()
{
	if (head != nullptr && head->children[0] != nullptr)//has at least two list elements
	{
		NodeType * grandparent{ head };
		NodeType * parent{ grandparent->children[0] };//store head's child so grandparent can change
		while (parent != nullptr)
		{
			NodeType * child{ parent->children[0] };//not a double pointer to store an address that won't change in the line below
			parent->children[0] = grandparent;//change the direction the middle node/parent points
			grandparent = parent;//move these two down one in the list
			parent = child;
		}
		head->children[0] = nullptr;//make new end of list at old first element
		head = grandparent;//make first element now last element
	}
}