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
	 * @brief Abstract class for any object with operator[] defined for unsigned int indices.
	 * 
	 * @tparam T Any typename, though in derived classes this may be restricted to a subset of typenames.
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


	template <typename T, unsigned int SIZE>
	TMAT getMinv(const unsigned int);

	template <typename T>
	T dist(const TVEC&, const TVEC);

	template <typename T>
	T magnitude(const TVEC&);

}

#include "numeric.tpp"