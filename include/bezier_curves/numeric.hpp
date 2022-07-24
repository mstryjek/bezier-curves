/**
 * @file numeric.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <Eigen/Core>

namespace Bezier::numeric{
	int selectSize(const int, const unsigned int);
	Eigen::Matrix<long int, Eigen::Dynamic, Eigen::Dynamic> getMinv(const unsigned int);
}