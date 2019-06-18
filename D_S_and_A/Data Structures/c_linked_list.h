#pragma once

#include <vector>

#include "c_poly_node.h"
#include "Iterators/c_linked_list_iterator.h"

template<class DataType, class NodeType = c_poly_node<DataType>>
class c_linked_list
{
	NodeType * tail = nullptr;
public:
	NodeType * head = nullptr;

	c_linked_list() = delete;
	explicit c_linked_list(DataType const& data);
	explicit c_linked_list(std::vector<DataType> const& data_list);
	
	c_linked_list(c_linked_list<DataType, NodeType>& other);//copy constructor
	c_linked_list<DataType, NodeType>& operator=(c_linked_list<DataType, NodeType>& other);//copy assignment operator

	c_linked_list(c_linked_list<DataType, NodeType>&& other) noexcept;//move constructor
	c_linked_list<DataType, NodeType>& operator=(c_linked_list<DataType, NodeType>&& other) noexcept;//move assignment operator

	~c_linked_list();

	NodeType * * operator[](int const& index);
	//NodeType& operator[](int const& index);//this is the goal to get working, I think, in all classes

	c_linked_list_iterator<DataType, NodeType> begin();
	c_linked_list_iterator<DataType, NodeType> end();

	void add_item(DataType const& data);
	void add_items(std::vector<DataType> const& data_list);
	void remove_item(DataType const& data);
	void remove_item_by_index(int const& index);

	size_t length();
	int amount_reoccurs(DataType const& data);
	bool detect_loop();
	size_t length_of_loop();
	void reverse();
};

#include "c_linked_list.inl"