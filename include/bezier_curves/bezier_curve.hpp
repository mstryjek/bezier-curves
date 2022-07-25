/**
 * @file bezier_curve.h
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
	class ICurve{
		public:
			virtual void at(const double, TVEC&) const = 0;
			virtual void point(const unsigned int, TVEC&) const = 0;
			virtual TMAT* getPoints(void) const = 0;
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class DerivativeBezierCurve : public virtual ICurve<T>{
		private:
			TMAT points;
			const numeric::IIndexable<T>* const factorials;
		public:
			DerivativeBezierCurve(const TMAT&, const numeric::IIndexable<T>* const);
			~DerivativeBezierCurve();
			virtual void at(const double, TVEC&) const override;
			virtual void point(const unsigned int, TVEC&) const override;
			virtual TMAT* getPoints(void) const override {return &this->points;}
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam DEGREE_ 
	 * @tparam DIMS_ 
	 */
	template <typename T, unsigned int DEGREE_, unsigned int DIMS_>
	class BezierCurve : public virtual ICurve<T>{
		private:
			TMAT points;
			ICurve<T>* firstOrderDerivative, secondOrderDerivative;
			numeric::Factorial<long unsigned int, DEGREE_+1>* const factorials;
			const TMAT Minv;

			void cleanUpDerivativeCurves(void);

			void computeTiValues(const TMAT&, TVEC&) const;
			void TMatrixFromTiValues(const TVEC&, TMAT&) const;

		public:
			BezierCurve(void);
			~BezierCurve();

			void fit(const TMAT&);
			T curvatureAt(const TVEC&) const;
			virtual void at(const double, TVEC&) const override;
			virtual void point(const unsigned int, TVEC&) const override;
	};
}

#include "bezier_curve.tpp"