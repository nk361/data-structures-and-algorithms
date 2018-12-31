#pragma once
#include <vector>

#include "c_comb_sort.h"

//O(n^2) but better than bubble sort in some cases when almost sorted
template<class MyType, typename Operation>
std::vector<MyType>& c_comb_sort<MyType, Operation>::sort(std::vector<MyType>& arr)
{
	Operation const op = Operation();

	int const shrink_interval = 13;
	int gap = static_cast<int>(arr.size());
	bool swapped{ true };
	
	while(gap != 1 || swapped)//in all cases, gap ends up as one. After gap is one, this will loop like bubble sort until sorted
	{
		gap = gap * 10 / shrink_interval;//reduce gap by 1.3, doing it at the start to be sure a pass will happen with a gap of one
		if (gap < 1)
			gap = 1;

		swapped = false;
		for(int i{ 0 }; i + gap < static_cast<int>(arr.size()); ++i)
			if(!op(arr[i], arr[i + gap]) && arr[i] != arr[i + gap])
			{
				std::swap(arr[i], arr[i + gap]);
				swapped = true;//to flag that it is possibly unsorted
			}
	}

	return arr;
}