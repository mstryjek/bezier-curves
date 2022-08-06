#include "bezier_curves/bezier_curve.hpp"
#include "bezier_curves/utils.hpp"

using namespace Bezier;

int main()
{
	Eigen::MatrixXd points(5, 2); 
	points << \
		100., 200.,
		150., 150.,
		200., 160.,
		300., 230.,
		400., 100.;

	cv::Mat img = cv::Mat::zeros({640, 480}, CV_8UC3);
	img.setTo(cv::Scalar(255, 255, 255));

	BezierCurve<double, 3, 2> curve;

	curve.fit(points);

	utils::drawBezierCurve(img, curve, 99);
	utils::drawControlPoints(img, curve, true);
	utils::drawPoints(img, points);

	cv::imshow("BEZIER", img);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return 0;
}