/**
 * @file factorials.h
 * @author your name (you@domain.com)
 * @brief
 * @date 2022-07-19
 */

#pragma once

#include <Eigen/Dense>

#include "templates.hpp"

namespace Bezier::numeric{


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 */
	template <typename T>
	class IIndexable{
		public:
			virtual T operator[](const unsigned int) const = 0;
	};


	/**
	 * @brief 
	 * 
	 * @tparam T 
	 * @tparam MAX_ 
	 */
	template <typename T, unsigned int MAX_>
	class Factorial : public virtual IIndexable<T>{
		private:
			TVEC factorials_;
		public:
			Factorial();
			~Factorial();
			virtual T operator[](const unsigned int) const override;
	};


	template <typename T>
	TMAT getMinv(const unsigned int);

	template <typename T>
	T dist(const TVEC&, const TVEC);

}

#include "numeric.tpp"