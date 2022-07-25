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
	: factorials_(Eigen::Matrix<T, Eigen::Dynamic, 1>(selectSize(DEGREE_, size), 1)), size(selectSize(DEGREE_, size))
{
	TEMPLATE_INTEGRAL
	TEMPLATE_NONZERO(MAX_)

	this->factorials_[0] =  1;

	for(unsigned int i=1; i<this->size; i++){
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
 * @param size 
 * @return TMAT 
 */
template <typename T>
TMAT Bezier::numeric::getMinv(const unsigned int size){
	TEMPLATE_ARITHMETIC(T)

	// TODO Math + function
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
T dist(const TVEC& start, const TVEC& end){
	TEMPLATE_ARITHMETIC(T)

	T distance = 0;
	for(unsigned int i=0; i<start.rows() && i<end.rows(); i++){
		distance += (end[i] - start[i])*(end[i] - start[i]);
	}
	return std::sqrt(distance);

}