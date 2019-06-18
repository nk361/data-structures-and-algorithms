#include "pch.h"

#include <vector>

#include "../../D_S_and_A/Algorithms/c_general_algorithms.h"

TEST(c_general_algorithms_header, c_small_general_algorithms)
{
	std::vector<int> sorted_vector{ 1, 2, 3, 4, 5 };
	c_general_algorithms::scramble_vals(sorted_vector);
	EXPECT_FALSE(sorted_vector[0] == 1 && sorted_vector[1] == 2 && sorted_vector[2] == 3 && sorted_vector[3] == 4 && sorted_vector[4] == 5);

	std::vector<std::string> sorted_strings{ "Amy", "Briana", "Cathy", "Darcy", "Emily", "Fatima", "Gracie", "Hannah" };
	c_general_algorithms::scramble_vals(sorted_strings);
	EXPECT_FALSE(sorted_strings[0] == "Amy" && sorted_strings[1] == "Briana" && sorted_strings[2] == "Cathy" && sorted_strings[3] == "Darcy" && sorted_strings[4] == "Emily" && sorted_strings[5] == "Fatima" && sorted_strings[6] == "Gretchen" && sorted_strings[7] == "Hannah");

	std::vector<int> const values_to_sum{ 5, 2, 9, 8, 4, 10, 15 };
	std::pair<int, int> twelve{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 12) };
	EXPECT_EQ(twelve.first, 8);
	EXPECT_EQ(twelve.second, 4);
	std::pair<int, int> nineteen{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 19) };
	EXPECT_EQ(nineteen.first, 9);
	EXPECT_EQ(nineteen.second, 10);
	std::pair<int, int> twenty{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 20) };
	EXPECT_EQ(twenty.first, 5);
	EXPECT_EQ(twenty.second, 15);
	std::pair<int, int> const fifty{ c_general_algorithms::pair_equal_to_sum(values_to_sum, 50) };
	EXPECT_TRUE(!fifty.first && !fifty.second);//Sum values not found

	//neither lambda function uses the index here, but still need to accept it to be called
	int(*multiply_sum)(int const&, int const&, int const&) { [](int const& index, int const& a, int const& b) { return a * b; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(1, 5, multiply_sum, 10, 2), 100);

	double(*add_three)(int const&, double const&, double const&, double const&) { [](int const& index, double const& a, double const& b, double const& c) { return a + b + c; } };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(1, 9, add_three, 5.5, 8.2, 10.7), 219.6);

	//lambda using the index
	double(*index_formula)(int const&, int const&) { [](int const& index, int const& x) { return pow(x, index + 2); } };//x^(n + 2)
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_sigma(-3, 5, index_formula, 4), 21845.25);

	int(*sum_arrays)(int const&, std::vector<int> const&, std::vector<int> const&) { [](int const& index, std::vector<int> const& a, std::vector<int> const& b) { return a[index] * b[index]; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(0, 2, sum_arrays, std::vector<int>{ 1, 2, 3 }, std::vector<int>{ 4, 5, 6 }), 32);

	double(*multiply_this)(int const&, double const&, double const&, double const&) { [](int const& index, double const& a, double const& b, double const& c) { return a * index + b * index + c * index; } };
	EXPECT_DOUBLE_EQ(c_general_algorithms::capital_pi(1, 3, multiply_this, 5.0, 2.0, 3.0), 6000.0);

	double(*multiple_types)(int const&, int const&, double const&) { [](int const& index, int const& x, double const& y) { return y * x; } };
	EXPECT_EQ(c_general_algorithms::capital_sigma(1, 10, multiple_types, 5, 8.2), 8.2 * 5 * 10);

	//int(*val_to_sum)(int const&) { [](int const& index) { return index * 10; } };
	//int(*sum_to_sum)(int const&, int const&, int const&, int(*)(int const&)) { [](int const& index, int const& strt, int const& nd, int(*v_t_s)(int const&)) { return c_general_algorithms::capital_sigma(strt, nd, v_t_s); } };
	//EXPECT_EQ(c_general_algorithms::capital_sigma(1, 10, sum_to_sum, 1, 10, val_to_sum), 5400);
}
