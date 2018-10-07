#pragma once
#include <array>

template<class MyType>
class c_bubble_sort
{
public:
	//O(n^2)
	//This sorting algorithm loops through the array from the start to the end
	//Checking two values next to each other and swapping if the left is larger
	//Each time through the largest number is found in the unsorted part
	//So it leaves one more spot at the end of the array out of the check each time until only the first two values are left to check
	MyType static *sort(MyType arr[], int const& size)
	{
		for (int i = size - 1; i >= 0; --i)
			for (int j = 0; j < i; ++j)
				if (arr[j] > arr[j + 1])
					std::swap(arr[j], arr[j + 1]);
		return arr;
	}
};