/**
 * @file templates.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-21
 */

#pragma once

#include "Eigen/Core"

#define TEMPLATE_INTEGRAL(T)      std::static_assert(std::is_integral<T>::value  , "Template parameter must be integral type!"      );
#define TEMPLATE_ARITHMETIC(T)    std::static_assert(std::is_arithmetic<T>::value, "Template type must be arithmetic!"              );
#define TEMPLATE_NONZERO(V)       std::static_assert(V != 0                      , "Template parameter must be positive!"           );
#define TMAT   	                  Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>
#define TVEC                      Eigen::Matrix<T, Eigen::Dynamic, 1>