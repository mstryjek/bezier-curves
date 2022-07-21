/**
 * @file bezier_curve.h
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-19
 */


#pragma once

#include "factorials.hpp"


namespace Bezier{

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, int DEGREE_, unsigned int DIMS_>
	class Curve{
		protected:
			const unsigned int size;
			const numeric::Factorial<unsigned int, DEGREE_> factorials;
			Eigen::Matrix<T, DEGREE_, DIMS_> points;
		public:
			Curve(const Eigen::Matrix<T, DEGREE_, DIMS_>&, const unsigned int = 0);
			~Curve();
			void at(const double, Eigen::Matrix<T, DIMS_, 1>&) const;
	};
}