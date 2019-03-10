#pragma once
#include <vector>

template<class MyType, int PivotType = 1, typename Operation = std::less<>>//default pivot is rightmost value
class c_quick_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_quick_sort.inl"