

#pragma once

/** @file  MathFunctions.h
 *  @brief Implementation of math utility functions.
 *
 */

#include <limits>

namespace Assimp
{
	namespace Math
	{

		// TODO: use binary GCD for unsigned integers ....
		template <typename IntegerType>
		inline IntegerType gcd(IntegerType a, IntegerType b)
		{
			const IntegerType zero = (IntegerType)0;
			while (true)
			{
				if (a == zero)
					return b;
				b %= a;

				if (b == zero)
					return a;
				a %= b;
			}
		}

		template <typename IntegerType>
		inline IntegerType lcm(IntegerType a, IntegerType b)
		{
			const IntegerType t = gcd(a, b);
			if (!t)
				return t;
			return a / t * b;
		}

		template <class T>
		inline T getEpsilon()
		{
			return std::numeric_limits<T>::epsilon();
		}

	}
}
