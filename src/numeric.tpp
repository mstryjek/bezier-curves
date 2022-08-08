/**
 * @file numeric.tpp
 * @author mstryjek
 * @brief Template implementations of extra numeric functions.
 * @date 2022-07-21
 */

#pragma once

#include "bezier_curves/numeric.hpp"



/**
 * @brief Calculate internal factorials.
 * 
 * @tparam T Any integral type
 * @tparam MAX_ Maximum factorial that will be accessed from this class. Must be 2 or greater
 */
template <typename T, unsigned int MAX_>
Bezier::numeric::Factorial<T, MAX_>::Factorial(void) 
	: factorials_(Eigen::Matrix<T, Eigen::Dynamic, 1>(MAX_))
{
	TEMPLATE_INTEGRAL(T)
	TEMPLATE_SIZE_V(MAX_)

	this->factorials_[0] =  1;

	for(unsigned int i=1; i<MAX_; i++){
		this->factorials_[i] =  this->factorials_[i-1] * i;
	}}





/**
 * @brief Default constructor.
 */
template <typename T, unsigned int MAX_>
Bezier::numeric::Factorial<T, MAX_>::~Factorial(void){
}


/**
 * @brief Get the precalculated factorial of a value.
 * 
 * @tparam T Any integral type
 * @tparam MAX_ Maximum factorial that will be accessed from this object
 * @param index Value, whose factorial is to be returned
 * @return Factorial of `index`
 */
template<typename T, unsigned int MAX_>
T Bezier::numeric::Factorial<T, MAX_>::operator[](const unsigned int index) const
{
	// Guard clause just in case
	if(index >= MAX_)
		throw std::out_of_range("Invalid index access!");
	
	return this->factorials_[index];
}



/**
 * @brief Get the inverted `M` matrix, generalized to any degree based on Jim Herold's original
 * degree-3 matrix
 * 
 * @tparam T Any arithmetic type, but floating point types work best
 * @tparam DEGREE_ Size of the square matrix
 * @return DEGREE_xDEGREE_ Eigen::Matrix equal to the inverse of `M`
 */
template <typename T, unsigned int DEGREE_>
TMAT Bezier::numeric::getMinv()
{
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DEGREE_)

	// Factorial table for matrix element computation
	Factorial<long unsigned int, DEGREE_+1> factorials;

	// Initlialize with zeros, since some elements of M (not inverted) are zero
	TMAT M = TMAT::Zero(DEGREE_+1, DEGREE_+1);

	// Fill with formula generalized from original 3x3 version
	// See article mentioned in README for explanation
	for(unsigned int i=0; i<=DEGREE_; i++){
		T rowFac = factorials[DEGREE_] / (T)(factorials[DEGREE_ - i] * factorials[i]);
		for(unsigned int j=0; j<=DEGREE_-i; j++){
			short int mul = (i + 1 + j)%2 == 0 ? 1 : -1;
			M(i, j) = rowFac * mul * factorials[DEGREE_-i] / (T)(factorials[DEGREE_ - i - j] * factorials[j]);
		}
	}

	return M.inverse();
}



/**
 * @brief Compute the euclidian distance between two points, given as the square root of
 * the sum of squares of differences between each pair of coordinates.
 * 
 * Order of arguments is irrelevant
 * 
 * @tparam T Any arithmetic type
 * @param start First point
 * @param end Second point
 * @return The euclidian distance between the two points 
 */
template <typename T>
T Bezier::numeric::dist(const TVEC& start, const TVEC& end){
	TEMPLATE_ARITHMETIC(T)

	T distance = 0.;
	for(unsigned int i=0; i<start.rows() && i<end.rows(); ++i){
		distance += (end[i] - start[i])*(end[i] - start[i]);
	}

	return (T) std::sqrt(distance);
}


/**
 * @brief Calculate the magnitude of a vector, given as the euclidian distance of its
 * end from origin.
 * 
 * @tparam T Any arithmetic type
 * @param vec Vector to calculate magintude of
 * @return Square root of sum of squares of vector elements
 */
template <typename T>
T Bezier::numeric::magnitude(const TVEC& vec){
	TEMPLATE_ARITHMETIC(T)
	ASSERT_NONZERO(vec.rows())

	T ssum = (T) 0.;

	for(unsigned int i=0; i<vec.rows(); i++){
		ssum += vec[i] * vec[i];
	}

	return (T) std::sqrt(ssum);

}