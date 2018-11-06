#pragma once
#include <vector>
#include "c_bubble_sort.h"

//O(n^2)
//This sorting algorithm loops through the vector from the start to the end
//Checking two values next to each other and swapping if the left is larger
//Each time through the largest number is found in the unsorted part
//So it leaves one more spot at the end of the vector out of the check each time until only the first two values are left to check
template<class MyType>
std::vector<MyType>& c_bubble_sort<MyType>::sort(std::vector<MyType>& arr)
{
	for (int i{ static_cast<int>(arr.size()) - 1 }; i >= 0; --i)
		for (int j{ 0 }; j < i; ++j)
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
	return arr;
}