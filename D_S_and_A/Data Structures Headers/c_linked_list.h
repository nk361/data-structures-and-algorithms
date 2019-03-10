#pragma once
#include <vector>

#include "Iterators/c_linked_list_iterator.h"

template <class ValType, template<class> class NodeType>
class c_linked_list
{
	NodeType<ValType> * tail = nullptr;
public:
	NodeType<ValType> * head = nullptr;

	c_linked_list() = delete;
	explicit c_linked_list(ValType const& val);
	explicit c_linked_list(std::vector<ValType> const& vals);

	c_linked_list(c_linked_list<ValType, NodeType>& other);//copy constructor
	c_linked_list<ValType, NodeType>& operator=(c_linked_list<ValType, NodeType>& other);//copy assignment operator

	c_linked_list(c_linked_list<ValType, NodeType>&& other) noexcept;//move constructor
	c_linked_list<ValType, NodeType>& operator=(c_linked_list<ValType, NodeType>&& other) noexcept;//move assignment operator

	~c_linked_list();

	NodeType<ValType> * * operator[](int const& index);

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
