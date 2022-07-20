/**
 * @file factorials.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Eigen/Dense>

#define TEMPLATE_EIGEN_COMAPTIBLE(T) typename = typename std::enable_if<std::isgreaterequal(T, -1), void>::type
#define TEMPLATE_NUMERIC(T) typename = typename std::enable_if<std::is_arithmetic<T>::value, void>::type

namespace Bezier::numeric{

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam MAX_ 
	 */
	template <typename T, int MAX_, TEMPLATE_EIGEN_COMAPTIBLE(MAX_), TEMPLATE_NUMERIC(T)>
	class Factorial{
		private:
			Eigen::Matrix<T, MAX_, 1> factorials_;

		public:
			Factorial(void);
			~Factorial(void);
			T operator[](const unsigned int index) const;
	};

}