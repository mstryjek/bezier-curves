/**
 * @file bezier_curve.tpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include "bezier_curves/bezier_curve.hpp"

template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::Curve<T, DEGREE_, DIMS_>::Curve(const Eigen::Matrix<T, DEGREE_, DIMS_>& superPoints, const unsigned int size = 1)
	: size(std::max(size, MAX_)), factorials(numeric::Factorial<unsigned int, DEGREE_>()), points(Eigen::Matrix<T, DEGREE_, DIMS_>())
{
	TEMPLATE_SIZE_OR_EIGEN_DYNAMIC(size, DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	for(unsigned int i=1; i<std::max(MAX_, size); i++){
		this->points[i-1] = superPoints[i] - superPoints[i-1];
	}

}