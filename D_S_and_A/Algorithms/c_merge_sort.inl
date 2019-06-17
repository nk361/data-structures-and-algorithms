#pragma once
#include <vector>

#include "c_merge_sort.h"

//O(nlogn)
template<class DataType, typename Operation>
std::vector<DataType>& c_merge_sort<DataType, Operation>::sort(std::vector<DataType>& arr)
{
	if (static_cast<int>(arr.size()) > 1)
	{
		Operation const op = Operation();
		
		std::vector<std::vector<DataType>> split_parts;//to hold vectors to merge

		//divide
		for (int i{ 0 }; i < static_cast<int>(arr.size()); ++i)
			split_parts.push_back({ arr[i] });

		//merge
		while (static_cast<int>(split_parts.size()) > 1)//merge until there is only one vector result
			for (int i{ 0 }; i < static_cast<int>(split_parts.size()) - 1; ++i)
			{
				int left{ 0 }, right{ 0 };
				while (left < static_cast<int>(split_parts[i].size()) && right < static_cast<int>(split_parts[i + 1].size()))//if left out of bounds, remaining right need added, if right out of bounds, all right added
					if (!op(split_parts[i][left], split_parts[i + 1][right]))//determine where numbers from right are less than numbers in left
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

				split_parts.erase(split_parts.begin() + i + 1);//remove right vector after values merged to left
			}

		arr = split_parts[0];//set the final merged vector with O(n) space to the original vector
	}

	return arr;
}