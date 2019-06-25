#pragma once

template <class DataType>
class c_heap_interface
{
	virtual DataType get_top() = 0;
	virtual void add_item(DataType const& val) = 0;
	virtual void add_items(std::vector<DataType> const& vals) = 0;
	virtual void remove_item() = 0;
};