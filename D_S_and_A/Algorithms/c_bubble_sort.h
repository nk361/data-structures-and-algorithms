#pragma once
#include <array>

namespace c_bubble_sort
{
	int *sort(int arr[], int size)
	{
		for (int i = size - 1; i >= 0; --i)// i = 9 goes 9 - 0
			for (int j = 0; j < i; ++j)//j = 0 goes 0 to (9 - 1) - 0
				if (arr[j] > arr[j + 1])
					std::swap(arr[j], arr[j + 1]);
		return arr;
	}
}