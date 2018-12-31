#pragma once
#include <vector>

template<class MyType, typename Operation = std::less<>>
class c_bubble_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_bubble_sort.inl"