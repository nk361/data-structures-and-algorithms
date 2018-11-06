#pragma once
#include <vector>
#include "c_counting_sort.h"

//O(nlogn)//using a map instead of a same size array to be able to deal with large numbers
//O(nlogn) is better than O(n + k) here with large gaps between values being sorted full of zeros where k can easily be many times larger than n
//This sorting algorithm first adds unique values from the array to a map, if they're already in the map, it increments their count
//After all unique values are counted, it adds the count of each spot to the spot's count behind it
//Lastly it adds elements to the array starting at the index of the new count value, the amount of times of the difference from the previous count value to the current
//if it is the first item, which has no previous, it subtracts zero for the amount of the current value to add to the array
template<class MyType>
std::vector<MyType>& c_counting_sort<MyType>::sort(std::vector<MyType>& arr)
{
	std::map<MyType, MyType> index_and_count;//map instead of unordered to keep indexes in order like an array
	for (int i{ 0 }; i < arr.size(); ++i)
	{
		typename std::map<MyType, MyType>::iterator found{ index_and_count.find(arr[i]) };
		if (found == index_and_count.end())//not found
			index_and_count.insert({ arr[i], 1 });//add "index" and count of 1//inserting into a map uses a red black tree with insertion of O(logn) but I use it n times if all values are unique
		else//found
			++found->second;//increment count
	}

	for (typename std::map<MyType, MyType>::iterator it{ std::next(index_and_count.begin(), 1) }; it != index_and_count.end(); ++it)//start AFTER first spot, go to last item
		it->second += std::prev(it, 1)->second;//adds count from item before the current

	for (typename std::map<MyType, MyType>::iterator it{ index_and_count.begin() }; it != index_and_count.end(); ++it)
		for (int i{ static_cast<int>(it->second - (it == index_and_count.begin() ? 0 : std::prev(it, 1)->second)) }; i > 0; --i)//start at the difference between current and previous for occorances
			arr[it->second - i] = it->first;//set arr at index occorances - how many placed equal to the current value
	return arr;
}