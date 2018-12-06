#pragma once
#include <vector>

#include "c_merge_sort.h"

//O(nlogn)
template<class MyType>
std::vector<MyType>& c_merge_sort<MyType>::sort(std::vector<MyType>& arr)
{
	if (arr.size() > 1)
	{
		std::vector<std::vector<MyType>> split_parts;//to hold vectors to merge
		bool const odd{ (arr.size() % 2 != 0) };//true if odd amount of values

		//divide
		for (int i{ 0 }; i < static_cast<int>(arr.size()) - odd; ++i)//loops one less time if odd to make group of two, loops n times if even
			if (odd && i == static_cast<int>(arr.size()) - 1 - 1)//if there's an odd amount, add the last two items into one vector for even amount of vectors
				if (arr[arr.size() - 1 - 1] > arr[arr.size() - 1])//add last two in sorted order
					split_parts.push_back({ arr[arr.size() - 1], arr[arr.size() - 1 - 1] });
				else
					split_parts.push_back({ arr[arr.size() - 1 - 1], arr[arr.size() - 1] });
			else//add all other single items
				split_parts.push_back({ arr[i] });

		//merge
		while (static_cast<int>(split_parts.size()) > 1)//merge until there is only one vector result
			for (int i{ 0 }; i < static_cast<int>(split_parts.size()) - 1; ++i)
			{
				int left{ 0 }, right{ 0 };
				while (left < static_cast<int>(split_parts[i].size()) && right < static_cast<int>(split_parts[i + 1].size()))//if left out of bounds, remaining right need added, if right out of bounds, all right added
					if (split_parts[i][left] >= split_parts[i + 1][right])//determine where numbers from right are less than numbers in left
					{
						split_parts[i].insert(split_parts[i].begin() + left, split_parts[i + 1][right]);//insert value from right before greater value from left
						++right;
					}
					else
						++left;
				while (right < static_cast<int>(split_parts[i + 1].size()))//add remaining values from right vector to left's end
				{
					split_parts[i].push_back(split_parts[i + 1][right]);
					++right;
				}

				split_parts.erase(split_parts.begin() + i + 1);//remove right merged vector
			}

		arr = split_parts[0];//set the final merged vector with O(n) space to the original vector
	}

	return arr;
}