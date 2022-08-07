/**
 * @file bezier_curve.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @date 2022-07-19
 */


#pragma once

#include "templates.hpp"
#include "numeric.hpp"

#include <cmath>
#include <stdexcept>
#include <sstream>


namespace Bezier{


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 */
	template <typename T>
	class IBaseBezierCurve{
		public:
			virtual void at(const double, TVEC&) const = 0;
			virtual const TMAT* const getControlPoints(void) const = 0;
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class DerivativeBezierCurve : public virtual IBaseBezierCurve<T>{
		private:
			TMAT controlPoints;
			const numeric::IIndexable<long unsigned int>* const factorials;
		public:
			DerivativeBezierCurve(const TMAT&, const numeric::IIndexable<long unsigned int>* const);
			~DerivativeBezierCurve();

			void controlPoint(const unsigned int i, TVEC& out) const {out = this->controlPoints.row(i);}

			virtual void at(const double, TVEC&) const override;
			virtual const TMAT* const getControlPoints(void) const override {return &(this->controlPoints);}
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class BezierCurve : public virtual IBaseBezierCurve<T>{
		private:
			TMAT controlPoints;
			IBaseBezierCurve<T> *firstOrderDerivative, *secondOrderDerivative;
			numeric::Factorial<long unsigned int, DEGREE_+1>* const factorials;
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