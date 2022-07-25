/**
 * @file utils.hpp
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-07-25
 */

#pragma once

#include "opencv2/opencv.hpp"
#include "bezier_curves/bezier_curve.hpp"


namespace Bezier::utils{

	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	void drawBezierCurve(cv::Mat& img, const BezierCurve<T, DEGREE_, DIMS_>&, const unsigned int);
	
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	void drawControlPoints(cv::Mat&, const BezierCurve<T, DEGREE_, DIMS_>&, const bool);

	template <typename T>
	void drawPoints(const TMAT&);

	template <typename T>
	cv::Point_<T> toCvPoint(const TVEC&);
}