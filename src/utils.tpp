/**
 * @file utils.tpp
 * @author mstryjek
 * @brief Utility function template implementations.
 * @date 2022-07-25
 */

#pragma once

#include "bezier_curves/utils.hpp"

using namespace Bezier;



/**
 * @brief Draw a Bezier curve on an image, with the given resolution.
 *
 * Template parameters can be inferred from curve object
 *
 * @tparam T Any arithmetic type
 * @tparam DEGREE_ Degree of the curve to be drawn. For compatibilty with curve templates
 * @tparam DIMS_ Dimensionality of the curve. Must be equal to 2 (since an image is 2-dimensional),
 * but the argument is here to avoid partial template spetialization of the curve class
 * @param img Image to draw on. Must be of type 8UC3
 * @param curve Curve to draw
 * @param resolution Number of equally spaced points on the curve to use to approximate it
 * @warning Color & other drawing parameters are hardcoded in this function, since it's
 * just a utility.
 */
template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
void Bezier::utils::drawBezierCurve(cv::Mat& img, const BezierCurve<T, DEGREE_, DIMS_>& curve, const unsigned int resolution)
{
	TEMPLATE_DRAWABLE(DIMS_)

	const cv::Scalar color(0, 255, 0); // FIXME Better colors
	const int thickness = 2;

	std::vector<cv::Point> points; points.reserve(resolution + 1);

	// Approximate the curve at resolution+1 points
	for(unsigned int i=0; i<=resolution; ++i){
		TVEC point;
		curve.at(double(i)/resolution, point);
		points.push_back(cv::Point(point[0], point[1]));
	}

	cv::polylines(img, points, false, color, thickness, cv::LINE_AA);
}


/**
 * @brief Draw the control points of a Bezier curve, and the lines connecting them
 * (curve 'skeleton') if specified.
 *
 * Template parameters can be inferred from curve object.
 *
 * @tparam T Any arithmetic type
 * @tparam DEGREE_ Degree of the curve. TParam for compatibility, will be inferred
 * @tparam DIMS_ Dimensionality of the curve. Must be equal to 2, since an image of 2-dimensional
 * @param img Image to draw on
 * @param curve Curve, whose control points will be drawn
 * @param connect Whether to also draw line segments connecting each sequential pair of control points
 * @warning Color & other drawing parameters are hardcoded in this function, since it's
 * just a utility.
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

	for(unsigned int i=0; i<DEGREE_; ++i){
		TVEC controlPoint; curve.controlPoint(i, controlPoint);

		if(connect){
			TVEC nextControlPoint;
			curve.controlPoint(i+1, nextControlPoint);

			cv::line(img, {int(controlPoint[0]), int(controlPoint[1])}, {int(nextControlPoint[0]), int(nextControlPoint[1])}, lineColor, lineThickness, cv::LINE_AA);
		}

		cv::circle(img, cv::Point(controlPoint[0], controlPoint[1]), pointRadius, pointColor, -1, cv::LINE_AA);
	}
}



/**
 * @brief Draw a set of points given as an `NxM` Eigen::Matrix on an image,
 * with `N` being the number of points and `M` being their dimensionality.
 *
 * @tparam T Matrix type. Supports any arithmetic type
 * @param img Image to draw the points on
 * @param points Matrix representing 
 * @warning Although this function will accept point of any dimensionality,
 * only the first 2 dimensions of points will be used as the `x` and `y` coordinates.
 * @warning Color & other drawing parameters are hardcoded in this function, since it's
 * just a utility.
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



