#pragma once
#include <vector>
#include <map>

template<class DataType, typename Operation = std::less<>>
class c_counting_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_counting_sort.inl"