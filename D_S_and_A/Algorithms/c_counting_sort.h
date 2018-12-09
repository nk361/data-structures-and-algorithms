#pragma once
#include <vector>
#include <map>

template<class MyType>
class c_counting_sort
{
public:
	std::vector<MyType> static& sort(std::vector<MyType>& arr);
};

#include "c_counting_sort.inl"