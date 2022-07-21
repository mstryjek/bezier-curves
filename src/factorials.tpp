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

#include "bezier_curves/factorials.hpp"



/**
 * @brief Construct a new Bezier::numeric::Factorial<T, MAX_>::Factorial object
 * 
 * @tparam T 
 * @tparam MAX_ 
 */
template <typename T, int MAX_>
Bezier::numeric::Factorial<T, MAX_>::Factorial(void): factorials_(Eigen::Matrix<T, MAX_, 1>(MAX_, 1)){
	TEMPLATE_ARITHMETIC(T)
	TEMPLATE_EIGEN_COMPATIBLE(MAX_)
	// Initialize the factorials vector with pre-calculated factorials
	// This way object constructor is O(n), but every subsequent factorial 'computation' (object index access) is O(1)
	this->factorials_[0] = (T) 1;

	for(unsigned int i=1; i<MAX_; i++){
		this->factorials_[i] = (T) this->factorials_[i-1] * i;
	}

}

/**
 * @brief Destroy the Bezier::numeric::Factorial<T, MAX_>::Factorial object
 * 
 * @tparam T 
 * @tparam MAX_ 
 */
template <typename T, int MAX_>
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
template<typename T, int MAX_>
T Bezier::numeric::Factorial<T, MAX_>::operator[](const unsigned int index) const{
	if(index >= MAX_)
		throw std::out_of_range("Invalid index access!");
	return this->factorials_[index];
}