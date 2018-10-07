#pragma once
#include <map>

class c_counting_sort
{
public:
	//O(n + k) where k is the amount of unique values
	//This algorithm only takes positive integer values to sort
	//This sorting algorithm first adds unique values from the array to a map, if they're already in the map, it increments their count
	//After all unique values are counted, it adds the count of each spot to the spot's count behind it
	//Lastly it adds elements to the array starting at the index of the new count value, the amount of times of the difference from the previous count value to the current
	//if it is the first item, which has no previous, it subtracts zero for the amount of the current value to add to the array
	unsigned int static *sort(unsigned int arr[], int const& size)
	{
		std::map<unsigned int, unsigned int> index_and_count;//map instead of unordered to keep indexes in order like an array
		for(int i = 0; i < size; ++i)
		{
			std::map<unsigned int, unsigned int>::iterator found = index_and_count.find(arr[i]);
			if (found == index_and_count.end())//not found
				index_and_count.insert({ arr[i], 1 });//add "index" and count of 1
			else//found
				++found->second;//increment count
		}

		for(std::map<unsigned int, unsigned int>::iterator it = std::next(index_and_count.begin(), 1); it != index_and_count.end(); ++it)//start AFTER first spot, go to last item
			it->second += std::prev(it, 1)->second;//adds count from item before the current

		for(std::map<unsigned int, unsigned int>::iterator it = index_and_count.begin(); it != index_and_count.end(); ++it)
			for (int i = it->second - (it == index_and_count.begin() ? 0 : std::prev(it, 1)->second); i > 0; --i)//start at the difference between current and previous for occorances
				arr[it->second - i] = it->first;//set arr at index occorances - how many placed equal to the current value
		return arr;
	}
};