/**
 * @file factorials.h
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-07-19
 */

#pragma once

#include <Eigen/Dense>

#include "templates.hpp"
#include "numeric.hpp"

namespace Bezier::numeric{

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam MAX_ 
	 */
	template <typename T, int MAX_>
	class Factorial{
		private:
			Eigen::Matrix<T, MAX_, 1> factorials_;
			const unsigned int size;
		public:
			Factorial(const unsigned int = 1);
			~Factorial();
			T operator[](const unsigned int) const;
	};


}

#include "factorials.tpp"