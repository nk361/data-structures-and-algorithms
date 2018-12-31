#pragma once
#include <vector>
//from data-structures-and-algorithms repo by Neil Kline, tested there
template<class MyType, typename Operation = std::less<>>
class c_merge_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_merge_sort.inl"