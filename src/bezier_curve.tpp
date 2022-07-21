/**
 * @file bezier_Curve_.tpp
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
Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_(const Eigen::Matrix<T, DEGREE_, DIMS_> * const superPoints, const unsigned int size = 1)
	: size(numeric::selectSize(DEGREE_, size)), 
	factorials(numeric::Factorial<long unsigned int, DEGREE_>(size)), 
	points(Eigen::Matrix<T, DEGREE_, DIMS_>())
{
	TEMPLATE_SIZE_OR_EIGEN_DYNAMIC(size, DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	if(superPoints != nullptr){
		for(unsigned int i=1; i<std::max(MAX_, size); i++){
			this->points[i-1] = *superPoints[i] - *superPoints[i-1];
		}
	}
}


/**
 * @brief Destroy the Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_ object
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::Curve_<T, DEGREE_, DIMS_>::~Curve_(){
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param t 
 * @param out 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
void Bezier::Curve_<T, DEGREE_, DIMS_>::at(const double t, Eigen::Matrix<T, DIMS_, 1>& out) const{
	for(unsigned int dim=0; dim<DIMS_; dim++){
		T res = (T) 0.;
		for(unsigned int i=0; i<this->size; i++){
			res += this->factorials[this->size-1] / (this->factorials[i] * this->factorials[this->size - 1 - i]) * 
				std::pow(t, i) * std::pow(1.-t, this->size - 1 - i) * this->points(i, dim);
		}
		out[dim] = res;
	}
}