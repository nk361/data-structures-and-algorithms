#pragma once
#include <vector>

#include "Iterators/c_linked_list_iterator.h"

template <class ValType, template<class> class NodeType>
class c_linked_list
{
	NodeType<ValType> * tail = nullptr;//pointer to pointer because tail is not a node in the list like head is, just a pointer to a possible last node
public:
	NodeType<ValType> * head = nullptr;

	c_linked_list() = delete;
	c_linked_list(ValType const& val);
	c_linked_list(std::vector<ValType> const& vals);

	~c_linked_list();

	NodeType<ValType> * * operator[](int index);

	c_linked_list_iterator<ValType, NodeType> begin();
	c_linked_list_iterator<ValType, NodeType> end();

	void add_item(ValType const& val);
	void add_items(ValType const& vals);
	void remove_item(ValType const& val);
	void remove_item_by_index(int const& index);

	size_t length();
	int amount_reoccurs(ValType const& val);
	bool detect_loop();
	size_t length_of_loop();
	void reverse();
};

#include "c_linked_list.inl"