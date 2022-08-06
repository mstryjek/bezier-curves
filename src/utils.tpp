/**
 * @file utils.tpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-25
 */

#pragma once

#include "bezier_curves/utils.hpp"

using namespace Bezier;



/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param img 
 * @param curve 
 * @param resolution 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::utils::drawBezierCurve(cv::Mat& img, const BezierCurve<T ,DEGREE_, DIMS_>& curve, const unsigned int resolution)
{
	TEMPLATE_DRAWABLE(DIMS_)

	const cv::Scalar color(0, 255, 0); // FIXME Better colors
	const int thickness = 2;

	std::vector<cv::Point> points; points.reserve(resolution + 1);

	for(unsigned int i=0; i<=resolution; ++i){
		TVEC point; curve.at(double(i)/resolution, point);
		points.push_back(cv::Point_<T>(point[0], point[1]));
	}

	cv::polylines(img, points, false, color, thickness, cv::LINE_AA);
}


/**
 * @brief 
 * 
 * @tparam T 
 * @tparam DEGREE_ 
 * @tparam DIMS_ 
 * @param img 
 * @param curve 
 * @param connect 
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::utils::drawControlPoints(cv::Mat& img, const BezierCurve<T, DEGREE_, DIMS_>& curve, const bool connect)
{
	TEMPLATE_DRAWABLE(DIMS_)

	// FIXME Better colors
	const cv::Scalar pointColor(255, 0, 0);
	const cv::Scalar lineColor(0, 0, 255);
	const unsigned int pointRadius = 3;
	const unsigned int lineThickness = 1;

	for(unsigned int i=0; i<DEGREE_-1; ++i){
		TVEC controlPoint; curve.controlPoint(i, controlPoint);

		if(connect){
			TVEC nextControlPoint; curve.controlPoint(i+1, nextControlPoint);
			cv::line(img, {controlPoint[0], controlPoint[1]}, {nextControlPoint[0], nextControlPoint[1]}, lineColor, lineThickness, cv::LINE_AA);
		}

		cv::circle(img, {controlPoint[0], controlPoint[1]}, pointRadius, pointColor, -1, cv::LINE_AA);
	}
	// FIXME Last control point may or may not be missing, check later
	// Also last line?
}



/**
 * @brief 
 * 
 * @tparam T 
 * @param img 
 * @param points 
 */
template <typename T>
void Bezier::utils::drawPoints(cv::Mat& img, const TMAT& points)
{
	// FIXME Tune values
	const cv::Scalar color(255, 0, 0);
	const int radius = 3;

	for(unsigned int i=0; i<points.rows(); ++i){
		TVEC pointEigen = points.row(i);
		cv::Point_<T> point = toCvPoint(pointEigen);
		cv::circle(img, point, radius, color, -1, cv::LINE_AA);
	}
}



