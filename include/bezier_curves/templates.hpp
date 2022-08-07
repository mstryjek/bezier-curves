/**
 * @file templates.hpp
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-07-21
 */

#pragma once

#include "Eigen/Core"

// Static assert a template typename parameter is integral. Will fail at compile-time if not
#define TEMPLATE_INTEGRAL(T) static_assert(std::is_integral<T>::value, "Template parameter must be integral type!");

// Static assert a template typename parameter is arithmetic. Will fail at compile-time if not
#define TEMPLATE_ARITHMETIC(T) static_assert(std::is_arithmetic<T>::value, "Template type must be arithmetic!");

// Static assert a template value paramter is not zero. Will fail at compile-time if not
#define TEMPLATE_NONZERO(V) static_assert(V != 0 , "Template parameter must be positive!");

// Static assert a call to a drawing function provides 2-dimensional points
#define TEMPLATE_DRAWABLE(V) static_assert(V == 2, "Call to template drawing function must be 2-dimensional!");

// Shorthand definition for a typename-T Eigen 2D matrix
#define TMAT Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>

// Shorthand definition for a typename-T Eigen vector
#define TVEC Eigen::Matrix<T, Eigen::Dynamic, 1>

// Runtime assert an argument value is between 0 and 1, both inclusive. Throws a runtime exception if violated
#define ASSERT_NORMALIZED(t) if(t < 0. || t > 1.){char errmsg[100];  \
								sprintf(errmsg, "Value of t must be normalized: got t=%.4f", t); \
								throw std::invalid_argument(errmsg);}

// Runtime assert the given matrix has the given number of dimensions (number of columns is considered to be dimensions). Throws a runtime exception if violated
#define ASSERT_DIMS(PTS, DIM) if(PTS.cols() != DIM){char errmsg[100]; \
								sprintf(errmsg, "Point matrix has incorrect dimensionality: expected %u, got %lu", DIMS_, points.cols()); \
								throw std::invalid_argument(errmsg);}

// Runtime assert a value is not zero. Throws a runtime exception if violated
#define ASSERT_NONZERO(V) if(V == 0){char errmsg[100]; \
							sprintf(errmsg, "Value is incorrect: %u, should be nonzero", V); \
							throw std::invalid_argument(errmsg);}

