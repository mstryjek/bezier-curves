/**
 * @file numeric.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-21
 */


#pragma once

#include "bezier_curves/numeric.hpp"


/**
 * @brief 
 * 
 * @param compileTimeOrDynamic 
 * @param runtime 
 * @return int 
 */
int Bezier::numeric::selectSize(const int compileTimeOrDynamic, const unsigned int runtime){
	if(compileTimeOrDynamic == Eigen::Dynamic) return runtime;
	return compileTimeOrDynamic;
}