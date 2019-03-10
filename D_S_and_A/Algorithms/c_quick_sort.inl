#pragma once
#include "time.h"

#include "c_quick_sort.h"

//O(n^2), average of O(nlogn)
template<class MyType, int PivotType, typename Operation>
std::vector<MyType>& c_quick_sort<MyType, PivotType, Operation>::sort(std::vector<MyType>& arr)
{
	if (static_cast<int>(arr.size()) > 1)
	{
		Operation op = Operation();

		int(*pivot_index)(int const&);//function pointer for finding our pivot every time

		if (PivotType == 0)
			pivot_index = [](int const& range) { return 0; };//leftmost
		else if (PivotType == 1)
			pivot_index = [](int const& range) { return range - 1; };//rightmost
		else if (PivotType == 2)
			pivot_index = [](int const& range) { return range / 2; };//middle
		else if (PivotType == 3)
		{
			srand(static_cast<unsigned int>(time(nullptr)));//initialize random once
			pivot_index = [](int const& range) { return static_cast<int>(floor(rand() % range)); };////random 0 to range - 1
		}
		else
			throw std::out_of_range("PivotType value out of range in c_quick_sort");

		//first left, right, and pivot indexes
		std::vector<int> left_right_pivot_indexes{ 0, static_cast<int>(arr.size() - 1), pivot_index(static_cast<int>(arr.size())) };//using this as a queue but adding and removing three items at a time
		
		while(!left_right_pivot_indexes.empty())//all groups of three indexes have been dealt with and all areas to the left and right of pivot had too few elements to have their index info added
		{
			int temp_left_index = left_right_pivot_indexes[0] - 1;//this always gets one added to it before use, no index out of bounds worries
			int temp_right_index = left_right_pivot_indexes[0];//one left of leftmost

			if(left_right_pivot_indexes[2] != left_right_pivot_indexes[1])//if pivot isnt rightmost, make it rightmost
			{
				std::swap(arr[left_right_pivot_indexes[2]], arr[left_right_pivot_indexes[1]]);
				left_right_pivot_indexes[2] = left_right_pivot_indexes[1];//update pivot index
			}

			while(temp_right_index < left_right_pivot_indexes[1])//temp right goes all the way to the end of the array
			{
				if(op(arr[temp_right_index], arr[left_right_pivot_indexes[2]]))//only move left if a value on the right needs swapped
				{
					++temp_left_index;
					std::swap(arr[temp_right_index], arr[temp_left_index]);
				}

				++temp_right_index;
			}

			std::swap(arr[temp_left_index + 1], arr[left_right_pivot_indexes[2]]);//swap one left of temp left with pivot
			left_right_pivot_indexes[2] = temp_left_index + 1;//update pivot index

			if(left_right_pivot_indexes[2] - 1 - left_right_pivot_indexes[0] > 0)//pivot and leftmost not the same and pivot and leftmost not side by side
			{
				//add left info
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[0]);//past left index
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[2] - 1);//one left of pivot
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[0] + pivot_index(left_right_pivot_indexes[left_right_pivot_indexes.size() - 1] - left_right_pivot_indexes[left_right_pivot_indexes.size() - 2] + 1));//get new pivot by adding the new left index along with a generated pivot index with a range from the difference between current right and left indexes that were just added to the vector
			}
			if(left_right_pivot_indexes[1] - left_right_pivot_indexes[2] + 1 > 1)//pivot and rightmost not the same and pivot and leftmost not side by side
			{
				//add right info
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[2] + 1);//including old pivot and over
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[1]);//past right index
				left_right_pivot_indexes.push_back(left_right_pivot_indexes[2] + 1 + pivot_index(left_right_pivot_indexes[left_right_pivot_indexes.size() - 1] - left_right_pivot_indexes[left_right_pivot_indexes.size() - 2] + 1));//get new pivot by taking previous pivot and adding the difference between current right and left indexes that were just added to the vector
			}
			
			left_right_pivot_indexes.erase(left_right_pivot_indexes.begin(), left_right_pivot_indexes.begin() + 3);//remove the first three items
		}
	}
	return arr;
}