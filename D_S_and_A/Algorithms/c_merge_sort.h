#pragma once
#include <vector>
//from data-structures-and-algorithms repo by Neil Kline, tested there
template<class DataType, typename Operation = std::less<>>
class c_merge_sort
{
public:
	std::vector<DataType> static& sort(std::vector<DataType>& arr);
};

#include "c_merge_sort.inl"