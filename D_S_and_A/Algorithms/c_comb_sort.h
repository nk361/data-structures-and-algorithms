#pragma once

#include <vector>

template<class DataType, typename Operation = std::less<>>
class c_comb_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_comb_sort.inl"