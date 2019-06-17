#pragma once
#include <vector>

template<class DataType, int PivotType = 1, typename Operation = std::less<>>//default pivot is rightmost value
class c_quick_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_quick_sort.inl"