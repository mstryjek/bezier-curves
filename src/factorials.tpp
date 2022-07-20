/**
 * @file factorials.tpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "bezier_curves/factorials.h"


/**
 * @brief Construct a new Bezier::numeric::Factorial<T, MAX_>::Factorial object
 * 
 * @tparam T 
 * @tparam MAX_ 
 */
template <typename T, int MAX_, TEMPLATE_EIGEN_COMAPTIBLE(MAX_), TEMPLATE_NUMERIC(T)>
Bezier::numeric::Factorial<T, MAX_>::Factorial(void): factorials_(Eigen::Matrix<T, MAX_, 1>(MAX_, 1)){
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
template <typename T, int MAX_, TEMPLATE_EIGEN_COMAPTIBLE(MAX_), TEMPLATE_NUMERIC(T)>
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
template <typename T, int MAX_, TEMPLATE_EIGEN_COMAPTIBLE(MAX_), TEMPLATE_NUMERIC(T)>
T Bezier::numeric::Factorial<T, MAX_>::operator[](const unsigned int index) const{
	return this->factorials_[index];
}
