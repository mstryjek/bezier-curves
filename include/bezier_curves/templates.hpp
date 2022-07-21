/**
 * @file templates.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-21
 */

#pragma once

#include "Eigen/Core"

// #define TEMPLATE_EIGEN_COMAPTIBLE(T) typename = typename std::enable_if<std::isgreaterequal(T, -1), void>::type
#define TEMPLATE_INTEGRAL(T)                   std::static_assert(std::is_integral<T>::value, "Template parameter must be integral type!");
#define TEMPLATE_ARITHMETIC(T) 		           std::static_assert(std::is_arithmetic<T>::value, "Template type must be arithmetic!")
#define TEMPLATE_EIGEN_COMPATIBLE(V)           std::static_assert(V > 1 || V == Eigen::Dynamic, "Invalid matrix dimensionality!");
#define TEMPLATE_SIZE_OR_EIGEN_DYNAMIC(V1, V2) std::static_assert((V1 > 1 || V1 == Eigen::Dynamic) && (V2 > 1 || V2 == Eigen::Dynamic), "Invalid template size or dynamic size!");
#define TEMPLATE_NONZERO(V)                    std::static_assert(V != 0, "Template parameter must be positive!");