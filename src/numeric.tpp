/**
 * @file factorials.tpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include "bezier_curves/numeric.hpp"



/**
 * @brief Construct a new Bezier::numeric::Factorial<T, MAX_>::Factorial object
 * 
 * @tparam T 
 * @tparam MAX_ 
 */
template <typename T, unsigned int MAX_>
Bezier::numeric::Factorial<T, MAX_>::Factorial(void) 
	: factorials_(Eigen::Matrix<T, Eigen::Dynamic, 1>(MAX_))
{
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(MAX_)

	this->factorials_[0] =  1;

	for(unsigned int i=1; i<MAX_; i++){
		this->factorials_[i] =  this->factorials_[i-1] * i;
	}}





/**
 * @brief Destroy the Bezier::numeric::Factorial<T, MAX_>::Factorial object
 * 
 * @tparam T 
 * @tparam MAX_ 
 */
template <typename T, unsigned int MAX_>
Bezier::numeric::Factorial<T, MAX_>::~Factorial(void){
}

/**
 * @brief 
 * 
 * @tparam T 
 * @tparam MAX_ 
 * @param index 
 * @return T 
 */
template<typename T, unsigned int MAX_>
T Bezier::numeric::Factorial<T, MAX_>::operator[](const unsigned int index) const
{
	if(index >= MAX_)
		throw std::out_of_range("Invalid index access!");
	return this->factorials_[index];
}



/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @return TMAT 
 */
template <typename T, unsigned int DEGREE_>
TMAT Bezier::numeric::getMinv(){
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_NONZERO(DEGREE_)

	Factorial<long unsigned int, DEGREE_+1> factorials;

	TMAT M = TMAT::Zero(DEGREE_+1, DEGREE_+1);

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
 * @brief 
 * 
 * @tparam T 
 * @param start 
 * @param end 
 * @return T 
 */
template <typename T>
T Bezier::numeric::dist(const TVEC& start, const TVEC& end){
	TEMPLATE_ARITHMETIC(T)

	T distance = 0.;
	for(unsigned int i=0; i<start.rows() && i<end.rows(); i++){
		distance += (end[i] - start[i])*(end[i] - start[i]);
	}

	return (T) std::sqrt(distance);
}


/**
 * @brief 
 * 
 * @tparam T 
 * @param vec 
 * @return T 
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