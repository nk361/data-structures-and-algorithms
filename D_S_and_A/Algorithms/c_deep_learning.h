#pragma once

#include <complex>
#include <algorithm>

namespace c_deep_learning
{
	//where z is graph input
	namespace c_activation
	{
		inline double linear(double const& z)
		{
			return z;
		}

		inline double sigmoid(double const& z)
		{
			return 1 / (1 + std::exp(-z));
		}

		inline double tanh(double const& z)
		{
			return 2 / (1 + std::exp(-2 * z)) - 1;
		}

		inline double relu(double const& z)
		{
			return std::max(0.0, z);
		}

		inline double leaky_relu(double const& z, double const& slope)
		{
			if (z < 0)
				return z * slope;
			return std::max(0.0, z);
		}
	}
	//where Y is the goal result
	namespace c_loss
	{
		
	}
	namespace c_optimization
	{
		
	}
}
