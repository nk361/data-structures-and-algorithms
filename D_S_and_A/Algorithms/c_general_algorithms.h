#pragma once

#include <cstdlib>
#include <ctime>
#include <unordered_map>

namespace c_general_algorithms
{
	//Kanade's array scramble algorithm in O(n) running the loop only n - 1 times
	//This algorithm takes a vector of any type, loops through it starting from the last element
	//and swaps the last element with a random element from the range of numbers that precede it
	//It does not loop on the first element becuase it has no range ahead of it
	template<class MyType>
	void static scramble_vals(std::vector<MyType>& vals)
	{
		srand(static_cast<unsigned int>(time(nullptr)));
		for (size_t i{ vals.size() - 1 }; i > 0; --i)
		{
			size_t ran{ static_cast<size_t>(floor(rand() % i)) };
			std::swap(vals[i], vals[ran]);
		}
	}

	//This algorithm takes a vector and the sum of two numbers from the vector that you want it to find
	//You must make sure that the values can have a sum, differece
	//It loops through the vector in O(n) looking for the supplement value to equal the sum
	//If it doesn't find it, it adds the current value to an unordered_map to be looked for later
	//If it does find it, the function returns THE FIRST pair of values in order that they are in in the vector that sum to the desired value
	//When no pair sum to the desired sum, a pair of two zeros is returned to be used in a check condition
	template<class ValTypes, class SumType>
	std::pair<ValTypes, ValTypes> static pair_equal_to_sum(std::vector<ValTypes> const& vals, SumType const& desired_sum)
	{
		std::unordered_map<ValTypes, ValTypes> encountered{};
		for (int i{ 0 }; i < static_cast<int>( vals.size() ); ++i)
		{
			typename std::unordered_map<ValTypes, ValTypes>::iterator found = encountered.find(desired_sum - vals[i]);
			if (found == encountered.end())
				encountered.insert({ vals[i], vals[i] });
			else
				return { desired_sum - vals[i], vals[i] };
		}
		return { 0, 0 };
	}

	//This function is meant to mimic the Capital Sigma symbol in math for summation
	//The first parameter of the function you pass is the index for what changes per iteration
	//It takes a start index, an end index, for the amount of times it will sum
	//After that it takes a function and the function's parameters that it will call and sum the returned value of
	template<class ReturnType, class ... Types>
	ReturnType capital_sigma(int const& start, int const& end, ReturnType (*f)(int const& index, Types const& ... args), Types const& ... args)
	{
		ReturnType overall_sum{ 0 };
		for (int i{ start }; i <= end; ++i)
			overall_sum += (*f)(i, args...);
		return overall_sum;
	}

	//This function is meant to mimic the Capital Pi symbol in math for product
	//This function is exactly like Capital Sigma/Summation except it multiplies function results instead of adding them
	template<class ReturnType, class ... Types>
	ReturnType capital_pi(int const& start, int const& end, ReturnType (*f)(int const& index, Types const& ... args), Types const& ... args)
	{
		ReturnType overall_product{ 1 };
		for (int i{ start }; i <= end; ++i)
			overall_product *= (*f)(i, args...);
		return overall_product;
	}
}