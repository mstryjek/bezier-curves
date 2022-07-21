/**
 * @file numeric.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-21
 */


#pragma once

#include "bezier_curves/numeric.hpp"


int Bezier::numeric::selectSize(int compileTimeOrDynamic, unsigned int runtime){
	if(compileTimeOrDynamic == Eigen::Dynamic) return runtime;
	return compileTimeOrDynamic;
}