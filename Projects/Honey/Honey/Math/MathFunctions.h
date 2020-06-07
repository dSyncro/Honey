#pragma once

#include <cmath>

namespace Honey {

	namespace Math::Functions {

		const float Pi = 3.14159265358979f;
		const float Degrees2Radians = (Pi * 2.0f) / 360.0f;
		const float Radians2Degrees = 360.0f / (Pi * 2.0f);

		const float Epsilon = FLT_EPSILON;

		const float NaN = NAN;
		const float Infinity = +INFINITY;
		const float NegativeInfinity = -INFINITY;

		inline float  Abs(float x) { return std::abs(x); }

		inline int    Sign(int x) { return -(x < 0); }
		inline float  Sign(float x) { return (float)(-(x < 0)); }

		inline bool IsPowerOfTwo(int x) { return x & !(x & (x - 1)) && x >= 0; }
		inline bool IsPowerOfTwo(unsigned int x) { return x & !(x & (x - 1)); }

		// Trigonometry

		/**
		 * Compute cosine of a value
		 * @param x The value to compute the cosine of (expressed in radians).
		 * @return The cosine of `x`.
		 */
		inline float  Cos(float x) { return std::cos(x); }

		/**
		 * Compute sine of a value
		 * @param x The value to compute the sine of (expressed in radians).
		 * @return The sine of `x`.
		 */
		inline float  Sin(float x) { return std::sin(x); }

		/**
		 * Compute tangent of a value
		 * @param x The value to compute the tangent of (expressed in radians).
		 * @return The tangent of `x`.
		 */
		inline float  Tan(float x) { return std::tan(x); }

		/**
		 * Compute arc cosine of a value
		 * @param x The value to compute the arc cosine of. Must be in range -1.0f to 1.0f.
		 * @return The arc cosine of `x` expressed in radians.
		 */
		inline float  Acos(float x) { return std::acos(x); }

		/**
		 * Compute arc sine of a value
		 * @param x The value to compute the arc sine of. Must be in range -1.0f to 1.0f.
		 * @return The arc sine of `x` expressed in radians.
		 */
		inline float  Asin(float x) { return std::asin(x); }

		/**
		 * Compute arc tangent of a value
		 * @param x The value to compute the arc tangent of.
		 * @return The arc tangent of `x` expressed in radians.
		 */
		inline float  Atan(float x) { return std::atan(x); }

		/**
		 * Compute arc tangent of y/x
		 * @param y The y component.
		 * @param x The x component.
		 * @return The arc tangent of `y/x` expressed in radians.
		 */
		inline float  Atan2(float y, float x) { return std::atan2(y, x); }

		// Hyperbolic

	#if 0

		/**
		 * Compute hyperbolic cosine of x
		 * @param x The value to compute the hyperbolic cosine of.
		 * @return The hyperbolic cosine of `x`.
		 */
		inline float  Cosh(float x) { return std::cosh(x); }

		/**
		 * Compute hyperbolic sine of x
		 * @param x The value to compute the hyperbolic sine of.
		 * @return The hyperbolic sine of `x`.
		 */
		inline float  Sinh(float x) { return std::sinh(x); }

		/**
		 * Compute hyperbolic tangent of x
		 * @param x The value to compute the hyperbolic tangent of.
		 * @return The hyperbolic tangent of `x`.
		 */
		inline float  Tanh(float x) { return std::tanh(x); }

		/**
		 * Compute hyperbolic arc cosine of x
		 * @param x The value to compute the hyperbolic arc cosine of.
		 * @return The hyperbolic arc cosine of `x` [0, +Inf].
		 */
		inline float  Acosh(float x) { return std::acosh(x); }

		/**
		 * Compute hyperbolic arc sine of x
		 * @param x The value to compute the hyperbolic arc sine of.
		 * @return The hyperbolic arc sine of `x` [0, +Inf].
		 */
		inline float  Asinh(float x) { return std::asinh(x); }

		/**
		 * Compute hyperbolic arc tangent of x
		 * @param x The value to compute the hyperbolic arc tangent of.
		 * @return The hyperbolic arc tangent of `x` [0, +Inf].
		 */
		inline float  Atanh(float x) { return std::atanh(x); }

	#endif

		// Exponential and Logarithmic
		inline float  Exp(float x) { return std::exp(x); }
		inline float  Exp2(float x) { return std::exp2(x); }
		inline float  Ln(float x) { return std::log(x); }
		inline float  Log2(float x) { return std::log2(x); }
		inline float  Log10(float x) { return std::log10(x); }
		inline float  Log(float base, float x) { return Log2(x) / Log2(base); }

		// Power
		inline float  Pow(float x, float y) { return std::pow(x, y); }
		inline float  Sqrt(float x) { return std::sqrt(x); }
		inline float  Cbrt(float x) { return std::cbrt(x); }

		// Rounding and remainder
		inline float  Ceil(float x) { return std::ceil(x); }
		inline float  Floor(float x) { return std::floor(x); }
		inline float  Truncate(float x) { return std::trunc(x); }
		inline float  Round(float x) { return std::round(x); }
		inline float  Mod(float x, float y) { return std::fmod(x, y); }
		inline float  Remainder(float x, float y) { return std::remainder(x, y); }

		// Min - max - difference
		inline float  Min(float x, float y) { return std::fmin(x, y); }
		inline float  Max(float x, float y) { return std::fmax(x, y); }
		inline float  PositiveDifference(float x, float y) { return std::fdim(x, y); }

		inline float  Clamp(float x, float min, float max) { return Min(max, Max(min, x)); }
		inline float  Clamp01(float x) { return Clamp(x, 0.0f, 1.0f); }

		inline bool ApproximatelyEquals(float x, float y) { return PositiveDifference(x, y) < Epsilon; }
	}

	namespace Mathf = Math::Functions;
}