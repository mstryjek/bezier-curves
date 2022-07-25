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
			virtual TMAT* getControlPoints(void) const = 0;
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
			const numeric::IIndexable<T>* const factorials;
		public:
			DerivativeBezierCurve(const TMAT&, const numeric::IIndexable<T>* const);
			~DerivativeBezierCurve();

			void controlPoint(const unsigned int i, TVEC& out) const {out = this->controlPoints.row(i);}

			virtual void at(const double, TVEC&) const override;
			virtual TMAT* getControlPoints(void) const override {return &(this->controlPoints);}
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

			void fit(const TMAT&);
			T curvatureAt(const double) const;
			virtual void at(const double, TVEC&) const override;
	};
}

#include "bezier_curve.tpp"