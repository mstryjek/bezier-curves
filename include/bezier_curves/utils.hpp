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
	void drawPoints(cv::Mat&, const TMAT&);

	/**
	 * @brief Convert 2-dimensional point from an Eigen::Vector form to a cv::Point
	 * 
	 * @tparam T 
	 * @param point Eigen::Vector with each element corresponding to the point's 
	 * coordinate in a different orthogonal dimension. The point must be 2-dimensional
	 * @return cv::Point_<T> 
	 */
	template <typename T>
	inline cv::Point_<T> toCvPoint(const TVEC& point){
		return cv::Point_<T>(point(0), point(1));
	}
}

#include "utils.tpp"