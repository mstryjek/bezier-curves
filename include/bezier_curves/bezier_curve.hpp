/**
 * @file bezier_curve.hpp
 * @author mstryjek
 * @brief Template class definitions for Bezier curve classes
 * @date 2022-07-19
 */


#pragma once

#include "macros.hpp"
#include "numeric.hpp"

#include <cmath>
#include <stdexcept>
#include <sstream>


namespace Bezier{


	/**
	 * @brief Abstract Bezier curve class (without degree/dimensionality template paraemters). Base for all Bezier Curve classes
	 * 
	 * @tparam T Supports any arithmetic type, but floating point types will work much better
	 */
	template <typename T>
	class IBaseBezierCurve{
		public:
			virtual void at(const double, TVEC&) const = 0;
			virtual const TMAT* const getControlPoints(void) const = 0;
	};


	/**
	 * @brief Class for a Bezier curve without the ability to be fitted to points.
	 * Control points and a precalculated factorial table must be provided from the object that instantiates this class.
	 * Not meant for standalone use, though it should work on its own.
	 * 
	 * @tparam T Supports any arithmetic type, floating point types preferred
	 * @tparam DEGREE_ Curve degree. Must be nonzero (TODO: switch to int, enable quadratic curves)
	 * @tparam DIMS_ Dimensionality of the Bezier curve. Obviously must be nonzero. Supports one-dimensional curves, though
	 * they don't have an obvious interpretation (they might be useful for interpolation, e.g. for animations)
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class DerivativeBezierCurve : public virtual IBaseBezierCurve<T>{
		private:
			/// (DEGREE_+1)xDIMS_ matrix (vector if DIMS_==1) holding control points for this curve
			/// Will be calculated from the creating curve's control points
			TMAT controlPoints;

			/// Pointer to the creating curve's factorials (there is no need to calculate a separate factorial table)
			const numeric::IIndexable<long unsigned int>* const factorials;
		public:
			DerivativeBezierCurve(const TMAT&, const numeric::IIndexable<long unsigned int>* const);
			~DerivativeBezierCurve();

			void controlPoint(const unsigned int i, TVEC& out) const {out = this->controlPoints.row(i);}

			virtual void at(const double, TVEC&) const override;
			virtual const TMAT* const getControlPoints(void) const override {return &(this->controlPoints);}
	};


	/**
	 * @brief Bezier Curve class. Describes an N-dimensional Bezier curve of any degree, starting with cubic (degree=3) curves,
	 * having 4 control points. Additionaly, allows for calculating the curvature at any point on the curve.
	 * 
	 * @tparam T Supports any arithmetic type, though floating point types offer much better precision
	 * @tparam DEGREE_ Degree of the curve. Curve of degree N will have N+1 control points. Must be >=3 (TODO: Allow for >=2)
	 * @tparam DIMS_ Dimensionality of the curve. Must be nonzero, but supports one-dimensional curves.
	 * 
	 * @link DerivativeBezierCurve @endlink
	 * 
	 * https://en.wikipedia.org/wiki/B%C3%A9zier_curve
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class BezierCurve : public virtual IBaseBezierCurve<T>{
		private:
			/// (DEGREE_+1)xDIMS_ matrix of control points
			/// Will be calculated during fitting
			TMAT controlPoints;

			/// Pointers to Bezier curves representing this curve's first and second derivatives (the derivative of a Bezier curve is another Bezier curve)
			IBaseBezierCurve<T> *firstOrderDerivative, *secondOrderDerivative;

			/// Precalculated factorial table, since calculating factorials multiple times is very inefficient
			numeric::Factorial<long unsigned int, DEGREE_+1>* const factorials;

			/// The matrix M^(-1) (since only the inverse is ever used), as described by Jim Herold
			/// See utils.hpp/Bezier::getMinv() for details
			const TMAT Minv;

			void cleanUpDerivativeCurves(void);

			void computeTiValues(const TMAT&, TVEC&) const;
			void TMatrixFromTiValues(const TVEC&, TMAT&) const;

		public:
			BezierCurve(void);
			~BezierCurve();

			void controlPoint(const unsigned int i, TVEC& out) const {out = this->controlPoints.row(i);}

			virtual const TMAT* const getControlPoints(void) const override {return &(this->controlPoints);}

			void fit(const TMAT&);
			T curvatureAt(const double) const;
			virtual void at(const double, TVEC&) const override;
	};

	// Template shorthands

	// Float-precision cubic curves
	using CubicBezierCurve2f = BezierCurve<float, 3, 2>;
	using CubicBezierCurve3f = BezierCurve<float, 3, 3>;
	// Double-precision cubic curves
	using CubicBezierCurve2d = BezierCurve<double, 3, 2>;
	using CubicBezierCurve3d = BezierCurve<double, 3, 3>;

	// Float-precision quartic curves
	using QuarticBezierCurve2f = BezierCurve<float, 4, 2>;
	using QuarticBezierCurve3f = BezierCurve<float, 4, 3>;
	// Double-precision quartic curves
	using QuarticBezierCurve2d = BezierCurve<double, 4, 2>;
	using QuarticBezierCurve3d = BezierCurve<double, 4, 3>;

	// Float-precision quintic curves
	using QuinticBezierCurve2f = BezierCurve<float, 5, 2>;
	using QuinticBezierCurve3f = BezierCurve<float, 5, 3>;
	// Double-precision quintic curves
	using QuinticBezierCurve2d = BezierCurve<double, 5, 2>;
	using QuinticBezierCurve3d = BezierCurve<double, 5, 3>;

}

#include "bezier_curve.tpp"