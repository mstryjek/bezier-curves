/**
 * @file bezier_curve.tpp
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-07-21
 */


#pragma once

#include "bezier_curves/bezier_curve.hpp"


/**
 * @brief Create a derivative curve from a parent curve
 *
 * @tparam T Any arithmetic type
 * @tparam DEGREE_ Degree of the derivative curve, which should be one less than the parent curve, but no less than 1 (TODO: enable down to 0, inclusive)
 * @tparam DIMS_ Curve dimensionality, should be same as parent curve dimensionality
 * @param superPoints Parent curve's control points
 * @param superFactorials Pointer to external factorial table object, since there is no need to instantiate another one
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::DerivativeBezierCurve(const TMAT& superPoints, const numeric::IIndexable<long unsigned int>* const superFactorials)
	: controlPoints(TMAT(DEGREE_+1, DIMS_)), factorials(superFactorials)
{
	TEMPLATE_NONZERO(DEGREE_)
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DIMS_)

	// Derivative Bezier curve's control points are differences between each two sequential control points of parent curve
	// For reference, see: https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-der.html
	for(unsigned int i=1; i<DEGREE_+1; i++){
		this->controlPoints(i-1) = superPoints(i) - superPoints(i-1);
	}
}


/**
 * @brief Default destructor
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::~DerivativeBezierCurve(){
}


/**
 * @brief Calcluate the value of a Bezier curve at a particular value of `t`
 *
 * @param t Value of `t` to evaluate at. Must be between 0 and 1
 * @param out Reference to output Eigen::Vector, containing the resulting point. Will be overwritten
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::DerivativeBezierCurve<T, DEGREE_, DIMS_>::at(const double t, TVEC& out) const
{
	ASSERT_NORMALIZED(t)

	out = TVEC(DIMS_);

	for(unsigned int dim=0; dim<DIMS_; dim++){
		T res =  0.;
		for(unsigned int i=0; i<DEGREE_+1; i++){
			res += (*(this->factorials))[DEGREE_] / ((*(this->factorials))[i] * ((*(this->factorials))[DEGREE_ - i])) *
				std::pow(t, i) * std::pow(1.-t, DEGREE_ - 1 - i) * this->controlPoints(i, dim);
		}
		out(dim) = res;
	}
}



/**
 * @brief Create an unintialized Bezier curve. The curve will be initialized once `.fit()` has been called
 *
 * @tparam T Any arithmetic type
 * @tparam DEGREE_ Degree of the Bezier curve. Cannot be lower than 3 (TODO: 2)
 * @tparam DIMS_ Dimensionality of the curve. Must be positive
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::BezierCurve()
	: firstOrderDerivative(nullptr), secondOrderDerivative(nullptr),
		factorials(new numeric::Factorial<long unsigned int, DEGREE_+1>()), Minv(numeric::getMinv<T, DEGREE_>())
{
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DEGREE_)
	TEMPLATE_NONZERO(DIMS_)
}


/**
 * @brief Destroy derivative curves, if any, as well as factorials allocated at creation.
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
Bezier::BezierCurve<T, DEGREE_, DIMS_>::~BezierCurve()
{
	this->cleanUpDerivativeCurves();
	if(this->factorials != nullptr)
		delete this->factorials;
}


/**
 * @brief Destroy derivative curves and replace the pointers with null pointers.
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
 * @brief Compute the `t_i` values for each point in the fitting set.
 *
 * @param points Points the curve is being fitted to
 * @param tiOut Outut vector of `t_i` for each point
 */
template <typename T, unsigned int DEGREE_,  unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::computeTiValues(const TMAT& points, TVEC& tiOut) const
{
	// Guard clause against sets of points in higher or lower dimensions than specified
	ASSERT_DIMS(points, DIMS_);

	tiOut = TVEC(points.rows());

	TVEC distances = TVEC::Zero(points.rows());

	// Compute distances from each point to the next
	for(unsigned int i=1; i<points.rows(); i++){
		TVEC cur = points.row(i), prev = points.row(i-1);
		distances[i] = numeric::dist(cur, prev) + distances[i-1];
	}

	// Normalize distances to [0, 1]
	for(unsigned int i=0; i<distances.rows(); i++){
		tiOut[i] = distances[i] / distances[distances.rows() - 1];
	}

}


/**
 * @brief Compute the matrix `T` from the vector of values `t_i`, given for each point.
 * This method is simply a shorthand, since the matrix `T` is simply an arrangement of `t_i` raised to consecutive powers.
 *
 * @param ti Precomputed Eigen::Vector of `t_i`
 * @param Tout Resulting matrix
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::TMatrixFromTiValues(const TVEC& ti, TMAT& Tout) const
{
	Tout = TMAT(ti.rows(), DEGREE_+1);

	for(unsigned int i=0; i<ti.rows(); ++i){
		for(int exp=DEGREE_; exp>=0; --exp){
			Tout(i, DEGREE_-exp) = std::pow(ti[i], exp);
		}
	}
}



/**
 * @brief Fit a Bezier curve to a set of points, given as an `NxM` matrix, `N` being the number of points and `M`
 * being their dimensionality. Note that the dimensionality must match the curve object's dimensionality template
 * argument. If the curve has been fitted before, all previous information will be lost
 * 
 * @param points Points to fit the curve to
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::fit(const TMAT& points)
{
	ASSERT_DIMS(points, DIMS_)

	TVEC Ti;
	this->computeTiValues(points, Ti);

	TMAT T_;
	this->TMatrixFromTiValues(Ti, T_);

	this->controlPoints = TMAT(DEGREE_+1, DIMS_);

	// HACK I must've missed a (-1) somewhere in the math, but putting it here for a quick fix
	// Will work as intended
	short int mul = DEGREE_%2 == 0? -1 : 1;
	TMAT rhs = mul * ( this->Minv * ((T_.transpose() * T_).inverse()) ) * T_.transpose();

	// Matrix multiplication on each dimension separately
	for(unsigned int dim=0; dim<DIMS_; dim++){
		this->controlPoints.col(dim) = rhs * points.col(dim);
	}

	// Set up new derivative curves to calculate curvature
	this->cleanUpDerivativeCurves();
	this->firstOrderDerivative  = new DerivativeBezierCurve<T, DEGREE_-1, DIMS_>(this->controlPoints,                               this->factorials);
	this->secondOrderDerivative = new DerivativeBezierCurve<T, DEGREE_-2, DIMS_>(*(this->firstOrderDerivative->getControlPoints()), this->factorials);
}


/**
 * @brief Evaluate the curve at a specific value of the parameter `t`
 *
 * @param t Value to evaluate at. Must be between 0 and 1 (inclusive)
 * @param out Resulting point (reference to an Eigen::Vector). Will be overwritten
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::BezierCurve<T, DEGREE_, DIMS_>::at(const double t, TVEC& out) const
{
	ASSERT_NORMALIZED(t)

	out = TVEC(DIMS_);

	// Evaluate at `t` for each dimension
	// TODO: Precalculate coefficients
	for(unsigned int dim=0; dim<DIMS_; dim++){
		T res =  0.;
		for(unsigned int i=0; i<=DEGREE_; i++){
			res += (*this->factorials)[DEGREE_] / ((*this->factorials)[i] * (*this->factorials)[DEGREE_ - i]) *
				std::pow(t, i) * std::pow(1.-t, DEGREE_ - i) * this->controlPoints(i, dim);
		}
		out[dim] = res;
	}
}


/**
 * @brief Calculate the curvature at a specific value of `t`. The curvature returned is always non-negative,
 * not including information about the its direction (which is non-trivial for higher-dimensional curves)
 *
 * @return The curvature value (which is 1/(radius of curvature)), in the inverse of whatever units the fitting
 * points were given in
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
T Bezier::BezierCurve<T, DEGREE_, DIMS_>::curvatureAt(const double t) const
{
	ASSERT_NORMALIZED(t)

	if(DEGREE_ == 1) return (T) 0.;

	using namespace numeric;

	TVEC firstDerivative; this->firstOrderDerivative->at(t, firstDerivative);
	TVEC secondDerivative; this->secondOrderDerivative->at(t, secondDerivative);

	T mag1 = magnitude(firstDerivative);
	T mag2 = magnitude(secondDerivative);
	T magDot = firstDerivative.dot(secondDerivative);

	// From https://en.wikipedia.org/wiki/Radius_of_curvature#In_n_dimensions
	T curvature  = std::fabs(
		std::sqrt(mag1 * mag1 * mag2 * mag2 - (magDot * magDot)) / 
			std::pow(mag1, 3.)
	);

	return curvature;

}

