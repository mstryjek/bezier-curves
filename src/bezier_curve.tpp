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
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::DerivativeBezierCurve(const TMAT& superPoints, const numeric::IIndexable<T>* const superFactorials)
	: points(TMAT(DEGREE_+1, DIMS_)), factorials(superFactorials)
{
	TEMPLATE_NONZERO(DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	for(unsigned int i=1; i<DEGREE_+1; i++){
		this->points[i-1] = superPoints[i] - superPoints[i-1];
	}
}


/**
 * @brief Destroy the Bezier::Curve_<T, DEGREE_, DIMS_>::Curve_ object
 *
 * @tparam T
 * @tparam DEGREE_
 * @tparam DIMS_
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::~DerivativeBezierCurve(){
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
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::at(const double t, TVEC& out) const
{
	out = TVEC(DIMS_);

	for(unsigned int dim=0; dim<DIMS_; dim++){
		T res =  0.;
		for(unsigned int i=0; i<DEGREE_+1; i++){
			res += *(this->factorials)[DEGREE_] / (*(this->factorials)[i] * *(this->factorials)[DEGREE_ - i]) *
				std::pow(t, i) * std::pow(1.-t, DEGREE_ - 1 - i) * this->points(i, dim);
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
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve() 
	: firstOrderDerivative(nullptr), secondOrderDerivative(nullptr),
		factorials(new numeric::Factorial<long unsigned int, DEGREE_+1>()), Minv(numeric::getMinv(DEGREE_))
{
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DEGREE_)
	TEMPLATE_NONZERO(DIMS_)
}

template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::~BezierCurve()
{
	this->cleanUpDerivativeCurves();
	if(this->factorials != nullptr)
		delete this->factorials;
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T ,DEGREE_, DIMS_>::cleanUpDerivativeCurves(){
	if(this->firstOrderDerivative != nullptr){
		delete this->firstOrderDerivative;
		this->firstOrderDerivative = nullptr;
	}

	if(this->secondOrderDerivative != nullptr){
		delete this->secondOrderDerivative;
		this->secondOrderDerivative = nullptr;
	}
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::fit(const TMAT& points)
{
	// TODO: Fitting


	this->cleanUpDerivativeCurves();
	this->firstOrderDerivative  = new DerivativeBezierCurve<T, DEGREE_-1, DIMS_>(this->points,                               this->factorials);
	this->secondOrderDerivative = new DerivativeBezierCurve<T, DEGREE_-2, DIMS_>(*(this->firstOrderDerivative->getPoints()), this->factorials);
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @return T 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
T Bezier::BezierCurve<T, DEGREE_, DIMS_>::curvatureAt(const TVEC& points) const
{
	// TODO
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param points 
 * @param tiOut 
 */
template <typename T, unsigned int DEGREE_,  unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::computeTiValues(const TMAT& points, TVEC& tiOut) const
{
	// Guard clause against sets of points in higher or lower dimensions than specified
	if(points.cols() != DIMS_){
		char errmsg[100];
		sprintf(errmsg, "Point matrix has incorrect dimensionality: expected %u, got %u", DIMS_, points.cols());
		throw std::invalid_argument(errmsg);
	}

	tiOut = TVEC(points.rows());

	TVEC distances(points.rows());
	distances[i] = 0;

	for(unsigned int i=1; i<points.rows(); i++){
		distances[i] = numeric::dist(points.row(i), points.row(i-1) + distances[i-1]);
	}

	for(unsigned int i=0; i<distances.rows(); i++){
		tiOut[i] = distances[i] / distances[distances.rows() - 1];
	}

}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param ti 
 * @param Tout 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::TMatrixFromTiValues(const TVEC& ti, TMAT& Tout) const
{
	Tout = TMAT(ti.rows(), DEGREE_+1);

	for(unsigned int i=0; i<ti.rows(); i++){
		for(unsigned int exp=DEGREE_; exp>=0; exp--){
			Tout(i, DEGREE_-exp) = std::pow(ti[i], exp);
		}
	}
}

