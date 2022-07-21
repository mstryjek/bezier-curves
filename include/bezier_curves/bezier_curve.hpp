/**
 * @file bezier_curve.h
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-19
 */


#pragma once

#include "factorials.hpp"
#include "numeric.hpp"

#include <cmath>

namespace Bezier{

	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, int DEGREE_, unsigned int DIMS_>
	class Curve_{
		protected:
			const unsigned int size;
			const numeric::Factorial<long unsigned int, DEGREE_> factorials;
			Eigen::Matrix<T, DEGREE_, DIMS_> points;
		public:
			Curve_(const Eigen::Matrix<T, DEGREE_, DIMS_>* const, const unsigned int = 1);
			~Curve_();
			void setPoints(const Eigen::Matrix<T, DEGREE_, DIMS_>&);
			void at(const double, Eigen::Matrix<T, DIMS_, 1>&) const;
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, int DEGREE_, unsigned int DIMS_>
	class BezierCurve : public Curve_<T, DEGREE_, DIMS_>{
		private:
			Curve_* firstOrderDerivative, secondOrderDerivative;
		public:
			BezierCurve(const unsigned int = 1);
			~BezierCurve();

			void fit(const Eigen::Matrix<T, DEGREE_, DIMS_>&);
			T curvatureAt(const Eigen::Matrix<T, DIMS_, 1>&) const;


	};
}