#pragma once

#include <cmath>

#include <Honey/Core.h>

namespace Honey {

	namespace Math::Functions {

		const float Pi = 3.14159265358979f;
		const float Degrees2Radians = Pi / 180.0f;
		const float Radians2Degrees = 180.0f / Pi;

		const float Epsilon = FLT_EPSILON;

		const float NaN = NAN;
		const float Infinity = +INFINITY;
		const float NegativeInfinity = -INFINITY;

		static HNY_ALWAYS_INLINE float  Abs(float x) noexcept { return std::abs(x); }

		static HNY_ALWAYS_INLINE int    Sign(int x) noexcept { return -(x < 0); }
		static HNY_ALWAYS_INLINE float  Sign(float x) noexcept { return (float)(-(x < 0)); }

		// Powers of 2

		static HNY_ALWAYS_INLINE bool IsPowerOfTwo(int x) noexcept { return x & !(x & (x - 1)) && x >= 0; }
		static HNY_ALWAYS_INLINE bool IsPowerOfTwo(unsigned int x) noexcept { return x & !(x & (x - 1)); }

		static HNY_ALWAYS_INLINE unsigned int NextPowerOfTwo(unsigned int x) noexcept
		{
			if (!x) return 0;

			x--;
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;

			return x++;
		}

		static HNY_ALWAYS_INLINE unsigned int PreviousPowerOfTwo(unsigned int x) noexcept
		{
			x |= x >> 1;
			x |= x >> 2;
			x |= x >> 4;
			x |= x >> 8;
			x |= x >> 16;
			return x - (x >> 1);
		}

		static HNY_ALWAYS_INLINE unsigned int ClosestPowerOfTwo(unsigned int x) noexcept
		{
			unsigned int nx = NextPowerOfTwo(x);
			unsigned int px = PreviousPowerOfTwo(x);
			return (nx - x) > (x - px) ? px : nx;
		}

		// Trigonometry

		/**
		 * @brief Compute cosine of a value
		 * @param x -> The value to compute the cosine of (expressed in radians).
		 * @return The cosine of `x`.
		 */
		static HNY_ALWAYS_INLINE float Cos(float x) noexcept { return std::cos(x); }

		/**
		 * @brief Compute sine of a value
		 * @param x -> The value to compute the sine of (expressed in radians).
		 * @return The sine of `x`.
		 */
		static HNY_ALWAYS_INLINE float Sin(float x) noexcept { return std::sin(x); }

		/**
		 * @brief Compute tangent of a value
		 * @param x -> The value to compute the tangent of (expressed in radians).
		 * @return The tangent of `x`.
		 */
		static HNY_ALWAYS_INLINE float Tan(float x) noexcept { return std::tan(x); }

		/**
		 * @brief Compute arc cosine of a value
		 * @param x -> The value to compute the arc cosine of. Must be in range -1.0f to 1.0f.
		 * @return The arc cosine of `x` expressed in radians.
		 */
		static HNY_ALWAYS_INLINE float Acos(float x) noexcept { return std::acos(x); }

		/**
		 * @brief Compute arc sine of a value
		 * @param x -> The value to compute the arc sine of. Must be in range -1.0f to 1.0f.
		 * @return The arc sine of `x` expressed in radians.
		 */
		static HNY_ALWAYS_INLINE float Asin(float x) noexcept { return std::asin(x); }

		/**
		 * @brief Compute arc tangent of a value
		 * @param x -> The value to compute the arc tangent of.
		 * @return The arc tangent of `x` expressed in radians.
		 */
		static HNY_ALWAYS_INLINE float Atan(float x) noexcept { return std::atan(x); }

		/**
		 * @brief Compute arc tangent of y/x
		 * @param y -> The y component.
		 * @param x -> The x component.
		 * @return The arc tangent of `y/x` expressed in radians.
		 */
		static HNY_ALWAYS_INLINE float Atan2(float y, float x) noexcept { return std::atan2(y, x); }

		// Hyperbolic

	#if 0

		/**
		 * Compute hyperbolic cosine of x
		 * @param x The value to compute the hyperbolic cosine of.
		 * @return The hyperbolic cosine of `x`.
		 */
		static HNY_ALWAYS_INLINE float  Cosh(float x) { return std::cosh(x); }

		/**
		 * Compute hyperbolic sine of x
		 * @param x The value to compute the hyperbolic sine of.
		 * @return The hyperbolic sine of `x`.
		 */
		static HNY_ALWAYS_INLINE float  Sinh(float x) { return std::sinh(x); }

		/**
		 * Compute hyperbolic tangent of x
		 * @param x The value to compute the hyperbolic tangent of.
		 * @return The hyperbolic tangent of `x`.
		 */
		static HNY_ALWAYS_INLINE float  Tanh(float x) { return std::tanh(x); }

		/**
		 * Compute hyperbolic arc cosine of x
		 * @param x The value to compute the hyperbolic arc cosine of.
		 * @return The hyperbolic arc cosine of `x` [0, +Inf].
		 */
		static HNY_ALWAYS_INLINE float  Acosh(float x) { return std::acosh(x); }

		/**
		 * Compute hyperbolic arc sine of x
		 * @param x The value to compute the hyperbolic arc sine of.
		 * @return The hyperbolic arc sine of `x` [0, +Inf].
		 */
		static HNY_ALWAYS_INLINE float  Asinh(float x) { return std::asinh(x); }

		/**
		 * Compute hyperbolic arc tangent of x
		 * @param x The value to compute the hyperbolic arc tangent of.
		 * @return The hyperbolic arc tangent of `x` [0, +Inf].
		 */
		static HNY_ALWAYS_INLINE float  Atanh(float x) { return std::atanh(x); }

	#endif

		// Exponential and Logarithmic
		static HNY_ALWAYS_INLINE float Exp(float x) noexcept { return std::exp(x); }
		static HNY_ALWAYS_INLINE float Exp2(float x) noexcept { return std::exp2(x); }
		static HNY_ALWAYS_INLINE float Ln(float x) noexcept { return std::log(x); }
		static HNY_ALWAYS_INLINE float Log2(float x) noexcept { return std::log2(x); }
		static HNY_ALWAYS_INLINE float Log10(float x) noexcept { return std::log10(x); }
		static HNY_ALWAYS_INLINE float Log(float base, float x) noexcept { return Log2(x) / Log2(base); }

		// Power
		static HNY_ALWAYS_INLINE float Pow(float x, float y) noexcept { return std::pow(x, y); }
		static HNY_ALWAYS_INLINE float Sqrt(float x) noexcept { return std::sqrt(x); }
		static HNY_ALWAYS_INLINE float Cbrt(float x) noexcept { return std::cbrt(x); }

		// Rounding and remainder
		static HNY_ALWAYS_INLINE float Ceil(float x) noexcept { return std::ceil(x); }
		static HNY_ALWAYS_INLINE float Floor(float x) noexcept { return std::floor(x); }
		static HNY_ALWAYS_INLINE float Truncate(float x) noexcept { return std::trunc(x); }
		static HNY_ALWAYS_INLINE float Round(float x) noexcept { return std::round(x); }
		static HNY_ALWAYS_INLINE float Mod(float x, float y) noexcept { return std::fmod(x, y); }
		static HNY_ALWAYS_INLINE float Remainder(float x, float y) noexcept { return std::remainder(x, y); }

		// Min - max - difference
		static HNY_ALWAYS_INLINE float Min(float x, float y) noexcept { return std::fmin(x, y); }
		static HNY_ALWAYS_INLINE float Max(float x, float y) noexcept { return std::fmax(x, y); }
		static HNY_ALWAYS_INLINE float PositiveDifference(float x, float y) noexcept { return std::fdim(x, y); }

		static HNY_ALWAYS_INLINE float Clamp(float x, float min, float max) noexcept { return Min(max, Max(min, x)); }
		static HNY_ALWAYS_INLINE float Clamp01(float x) noexcept { return Clamp(x, 0.0f, 1.0f); }

		static HNY_ALWAYS_INLINE bool ApproximatelyEquals(float x, float y) noexcept { return PositiveDifference(x, y) < Epsilon; }
	}

	namespace Mathf = Math::Functions;
}