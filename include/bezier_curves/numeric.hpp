/**
 * @file numeric.hpp
 * @author mstryjek
 * @brief Extra numeric functions for Bezier curve fitting, not encapsulated in Bezier curve classes
 * @date 2022-07-19
 */

#pragma once

#include <Eigen/Dense>

#include "macros.hpp"

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
	 * @brief Factorial table class, for a precalculated array of factorials. This is because there are many
	 * factorials calculated during the evaluation of a Bezier curve. Memory complexity of this object is O(N), and 
	 * instantiation time complexity is O(N), N being `MAX_`, but every subsequent lookup (factorial "computation") is O(1)
	 * 
	 * @tparam T Any integral type
	 * @tparam MAX_ Maximum number, whose factorial is stored in the object
	 */
	template <typename T, unsigned int MAX_>
	class Factorial : public virtual IIndexable<T>{
		private:
			/// MAX_-long vector (MAX_x1 matrix) of numbers, with the value under each index corresponding to that
			/// index' factorial (e.g. factorials_[0] is 1, factorials_[4] is 24)
			TVEC factorials_;
		public:
			Factorial();
			~Factorial();
			virtual T operator[](const unsigned int) const override;
	};


	template <typename T, unsigned int SIZE>
	TMAT getMinv(const unsigned int);

	template <typename T>
	T dist(const TVEC&, const TVEC&);

	template <typename T>
	T magnitude(const TVEC&);

}

#include "numeric.tpp"