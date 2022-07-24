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


/**
 * @brief Construct a new Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_ object
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param superPoints 
 * @param size 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_(const Eigen::Matrix<T, DEGREE_, DIMS_>* const superPoints, const unsigned int size)
	: size(numeric::selectSize(DEGREE_, size)), points(Eigen::Matrix<T, DEGREE_, DIMS_>())
{
	TEMPLATE_SIZE_OR_EIGEN_DYNAMIC(size, DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	if(superPoints != nullptr){
		for(unsigned int i=1; i<this->size; i++){
			this->points[i-1] = *superPoints[i] - *superPoints[i-1];
		}
	}
}

/**
 * @brief Construct a new Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_ object
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param superPoints 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_(const Eigen::Matrix<T, DEGREE_, DIMS_>* const superPoints)
	: size(DEGREE_), points(Eigen::Matrix<T, DEGREE_, DIMS_>())
{
	TEMPLATE_SIZE_V(DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	if(superPoints != nullptr){
		for(unsigned int i=1; i<this->size; i++){
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
void Bezier::Curve_<T, DEGREE_, DIMS_>::at(const double t, Eigen::Matrix<T, DIMS_, 1>& out, const numeric::Factorial<T, DEGREE_>& factorial) const{
	
	out = Eigen::Matrix<T, DIMS_, 1>();
	
	for(unsigned int dim=0; dim<DIMS_; dim++){
		T res = (T) 0.;
		for(unsigned int i=0; i<this->size; i++){
			res += factorial[this->size-1] / (factorial[i] * factorial[this->size - 1 - i]) * 
				std::pow(t, i) * std::pow(1.-t, this->size - 1 - i) * this->points(i, dim);
		}
		out[dim] = res;
	}
}



/**
 * @brief Construct a new Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve object
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param size 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve(const unsigned int size) : Curve_(nullptr, size), 
	firstOrderDerivative(nullptr), secondOrderDerivative(nullptr), 
	factorials(numeric::Factorial<T, DEGREE_>(numeric::selectSize(DEGREE_, size))), 
	Minv(numeric::getMinv(numeric::selectSize(DEGREE_, size)))
{
	


}



/**
 * @brief Construct a new Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve object
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param size 
 */
template <typename T, int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve(void) : Curve_(nullptr), 
	firstOrderDerivative(nullptr), secondOrderDerivative(nullptr), 
	factorials(numeric::Factorial<T, DEGREE_>(DEGREE_)), 
	Minv(numeric::getMinv(DEGREE_))
{
	

	
}