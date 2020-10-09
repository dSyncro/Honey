#pragma once

#include <cmath>
#include <limits>

#include <Honey/Core.h>

namespace Honey {

	namespace Math::Functions {

		/**
		 * @brief Famous pi constant.
		 * It express the ratio between a circumference and its diameter.
		 * @return Pi.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> pi() { return static_cast<T>(3.14159265358979); }

		/**
		 * @brief Multiply to this constant to convert easily
		 * from degrees to radians.
		 * @return degrees to radians conversion factor.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> degrees2Radians() { return pi<T>() / static_cast<T>(180.0); }

		/**
		 * @brief Multiply to this constant to convert easily
		 * from radians to degrees.
		 * @return radians to degrees conversion factor.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> radians2Degrees() { return static_cast<T>(180.0) / pi<T>(); }

		/**
		 * @brief The machine epsilon, that is, the difference between 
		 * 1.0 and the next value representable by the floating-point type.
		 * @tparam T Floating point type.
		 * @return Epsilon of the related type on this machine.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> epsilon() { return std::numeric_limits<T>::epsilon(); }

		/**
		 * @brief The quiet not-a-number value.
		 * @tparam T Floating point type.
		 * @return Quiet NaN of T.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> NaN() { return std::numeric_limits<T>::quiet_NaN(); }

		/**
		 * @brief Positive infinity constant.
		 * @tparam T Floating point type.
		 * @return Positive infinity of T.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> infinity() { return +std::numeric_limits<T>::infinity(); }

		/**
		 * @brief Negative infinity constant.
		 * @tparam T Floating point type.
		 * @return negative infinity of T.
		*/
		template <typename T = Float>
		constexpr EnableIfFloatingPoint<T> negativeInfinity() { return -infinity(); }

		/**
		 * @brief Get absolute value of a number.
		 * @param x The number.
		 * @return Absolute value of number.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> abs(T x) noexcept { return std::abs(x); }

		/**
		 * @brief Get sign of a value.
		 * @param x The value.
		 * @return Sign of x.
		*/
		template <typename T = Int>
		static HNY_ALWAYS_INLINE EnableIfSignedInt<T> sign(T x) noexcept { return -(x < 0); }

		/**
		 * @brief Get sign of a value.
		 * @param x The value.
		 * @return Sign of x.
		 * @overload
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<T> sign(T x) noexcept { return static_cast<T>(-(x < 0)); }

		// Powers of 2

		/**
		 * @brief Check if value is a power of two.
		 * @param x The value.
		*/
		template <typename T = Int>
		static HNY_ALWAYS_INLINE bool isPowerOfTwo(EnableIfSignedInt<T> x) noexcept { return x & !(x & (x - 1)) && x >= 0; }

		/**
		 * @brief Check if value is a power of two.
		 * @param x The value.
		*/
		template <typename T = UInt>
		static HNY_ALWAYS_INLINE bool isPowerOfTwo(EnableIfUnsignedInt<T> x) noexcept { return x & !(x & (x - 1)); }

		/**
		 * @brief Get next power of two.
		 * @param x The value.
		 * @return The nearest power of two bigger than x.
		*/
		template <typename T = UInt>
		static HNY_ALWAYS_INLINE EnableIfUnsignedInt<T> nextPowerOfTwo(T x) noexcept
		{
			if (!x) return 0;

			x--;

			for (UInt i = 1; i < sizeof(x) * 8; i <<= 1)
				x |= x >> i;

			return ++x;
		}

		/**
		 * @brief Get previous power of two.
		 * @param x The value.
		 * @return The nearest power of two smaller than x.
		*/
		template <typename T = UInt>
		static HNY_ALWAYS_INLINE EnableIfUnsignedInt<T> previousPowerOfTwo(T x) noexcept
		{
			if (!x) return 0;

			for (UInt i = 1; i < sizeof(x) * 8; i <<= 1)
				x |= x >> i;

			return x - (x >> 1);
		}

		/**
		 * @brief Get closest power of two.
		 * @param x The value.
		 * @return The power of two nearest to x.
		*/
		template <typename T = UInt>
		static HNY_ALWAYS_INLINE EnableIfUnsignedInt<T> closestPowerOfTwo(T x) noexcept
		{
			T nx = nextPowerOfTwo<T>(x);
			T px = previousPowerOfTwo<T>(x);
			return (nx - x) > (x - px) ? px : nx;
		}

		// Trigonometry

		/**
		 * @brief Compute cosine of a value
		 * @param x -> The value to compute the cosine of (expressed in radians).
		 * @return The cosine of `x`.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> cos(EnableIfArithmetic<ValueType> x) noexcept { return std::cos(x); }

		/**
		 * @brief Compute sine of a value
		 * @param x -> The value to compute the sine of (expressed in radians).
		 * @return The sine of `x`.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> sin(EnableIfArithmetic<ValueType> x) noexcept { return std::sin(x); }

		/**
		 * @brief Compute tangent of a value
		 * @param x -> The value to compute the tangent of (expressed in radians).
		 * @return The tangent of `x`.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> tan(EnableIfArithmetic<ValueType> x) noexcept { return std::tan(x); }

		/**
		 * @brief Compute arc cosine of a value
		 * @param x -> The value to compute the arc cosine of. Must be in range -1.0f to 1.0f.
		 * @return The arc cosine of `x` expressed in radians.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> acos(EnableIfArithmetic<ValueType> x) noexcept { return std::acos(x); }

		/**
		 * @brief Compute arc sine of a value
		 * @param x -> The value to compute the arc sine of. Must be in range -1.0f to 1.0f.
		 * @return The arc sine of `x` expressed in radians.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> asin(EnableIfArithmetic<ValueType> x) noexcept { return std::asin(x); }

		/**
		 * @brief Compute arc tangent of a value
		 * @param x -> The value to compute the arc tangent of.
		 * @return The arc tangent of `x` expressed in radians.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> atan(EnableIfArithmetic<ValueType> x) noexcept { return std::atan(x); }

		/**
		 * @brief Compute arc tangent of y/x
		 * @param y -> The y component.
		 * @param x -> The x component.
		 * @return The arc tangent of `y/x` expressed in radians.
		 */
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> atan2(EnableIfArithmetic<ValueType> y, ValueType x) noexcept { return std::atan2(y, x); }

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

		/**
		 * @brief Compute exponential function.
		 * @param x The value of the exponent.
		 * @return The base-e exponential function of x, which is e raised to the power x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> exp(EnableIfArithmetic<ValueType> x) noexcept { return std::exp(x); }

		/**
		 * @brief Compute binary exponential function.
		 * @param x The value of the exponent.
		 * @return The base-2 exponential function of x, which is 2 raised to the power x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> exp2(EnableIfArithmetic<ValueType> x) noexcept { return std::exp2(x); }

		/**
		 * @brief Compute natural logarithm.
		 * @param x The value whose logarithm is calculated.
		 * @return The natural logarithm of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> ln(EnableIfArithmetic<ValueType> x) noexcept { return std::log(x); }

		/**
		 * @brief Compute base-2 logarithm.
		 * @param x The value whose logarithm is calculated.
		 * @return The base-2 logarithm of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> log2(EnableIfArithmetic<ValueType> x) noexcept { return std::log2(x); }

		/**
		 * @brief Compute base-10 logarithm.
		 * @param x The value whose logarithm is calculated.
		 * @return The base-10 logarithm of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> log10(EnableIfArithmetic<ValueType> x) noexcept { return std::log10(x); }


		/**
		 * @brief Compute logarithm of arbitrary base.
		 * @param base The base.
		 * @param x The value whose logarithm is calculated.
		 * @return The base-n logarithm of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> log(EnableIfArithmetic<ValueType> base, ValueType x) noexcept { return log2(x) / log2(base); }

		// Power

		/**
		 * @brief Compute the power of x elevated by y.
		 * @param x The base.
		 * @param y The exponent.
		 * @return The power of x elevated by y.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> pow(EnableIfArithmetic<ValueType> x, ValueType y) noexcept { return std::pow(x, y); }

		/**
		 * @brief Compute the square root of a value.
		 * @param x The value.
		 * @return The square root of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> sqrt(EnableIfArithmetic<ValueType> x) noexcept { return std::sqrt(x); }

		/**
		 * @brief Compute the cube root of a value.
		 * @param x The value.
		 * @return The cube root of x.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> cbrt(EnableIfArithmetic<ValueType> x) noexcept { return std::cbrt(x); }

		// Rounding and remainder

		/**
		 * @brief Rounds x upward, returning the smallest integral value that is not less than x.
		 * @param x Value to round up.
		 * @return The smallest integral value that is not less than x (as a floating-point value).
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<T> ceil(T x) noexcept { return std::ceil(x); }

		/**
		 * @brief Rounds x upward, returning the smallest integral value that is not less than x.
		 * @param x Value to round up.
		 * @return The smallest integral value that is not less than x (as an integer value).
		*/
		template <typename FloatType = Float, typename IntType = Int>
		static HNY_ALWAYS_INLINE EnableIfIntegral<IntType> ceilToInt(EnableIfFloatingPoint<FloatType> x) noexcept { return static_cast<IntType>(ceil(x)); }

		/**
		 * @brief Rounds x downward, returning the largest integral value that is not greater than x.
		 * @param x Value to round down.
		 * @return The value of x rounded downward (as a floating-point value).
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<T> floor(T x) noexcept { return std::floor(x); }

		/**
		 * @brief Rounds x downward, returning the largest integral value that is not greater than x.
		 * @param x Value to round down.
		 * @return The value of x rounded downward (as an integer value).
		*/
		template <typename FloatType = Float, typename IntType = Int>
		static HNY_ALWAYS_INLINE EnableIfIntegral<IntType> floorToInt(EnableIfFloatingPoint<FloatType> x) noexcept { return static_cast<IntType>(floor(x)); }

		/**
		 * @brief Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
		 * @param x Value to truncate.
		 * @return The nearest integral value that is not larger in magnitude than x (as a floating-point value).
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<T> truncate(T x) noexcept { return std::trunc(x); }

		/**
		 * @brief Rounds x toward zero, returning the nearest integral value that is not larger in magnitude than x.
		 * @param x Value to truncate.
		 * @return The nearest integral value that is not larger in magnitude than x (as an integer value).
		*/
		template <typename FloatType = Float, typename IntType = Int>
		static HNY_ALWAYS_INLINE EnableIfIntegral<IntType> truncateToInt(EnableIfFloatingPoint<FloatType> x) noexcept { return static_cast<IntType>(truncate(x)); }

		/**
		 * @brief Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
		 * @param x Value to round.
		 * @return The value of x rounded to the nearest integral (as a floating-point value).
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<T> round(T x) noexcept { return std::round(x); }

		/**
		 * @brief Returns the integral value that is nearest to x, with halfway cases rounded away from zero.
		 * @param x Value to round.
		 * @return The value of x rounded to the nearest integral (as an integer value).
		*/
		template <typename FloatType = Float, typename IntType = Int>
		static HNY_ALWAYS_INLINE EnableIfIntegral<IntType> roundToInt(EnableIfFloatingPoint<FloatType> x) noexcept { return static_cast<IntType>(round(x)); }

		/**
		 * @brief Returns the floating-point remainder of numer/denom (rounded towards zero):
		 * fmod = numer - tquot * denom
		 * Where tquot is the truncated (i.e., rounded towards zero) result of: numer/denom.
		 * A similar function, remainder, returns the same but with the quotient rounded to the nearest integer (instead of truncated).
		 * @param x Value of the quotient numerator.
		 * @param y Value of the quotient denominator.
		 * @return The remainder of dividing the arguments.
		 * If denom is zero, the function may either return zero or cause a domain error 
		 * (depending on the library implementation).
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> mod(EnableIfArithmetic<ValueType> x, ValueType y) noexcept { return std::fmod(x, y); }

		/**
		 * @brief Returns the floating-point remainder of numer/denom (rounded to nearest):
		 * remainder = numer - rquot * denom
		 * Where rquot is the result of: numer/denom, rounded toward the nearest integral value (with halfway cases rounded toward the even number).
		 * A similar function, mod, returns the same but with the quotient truncated (rounded towards zero) instead.
		 * @param x Value of the quotient numerator.
		 * @param y Value of the quotient denominator.
		 * @return The remainder of dividing the arguments.
		*/
		template <typename ValueType = Float, typename RetType = Float>
		static HNY_ALWAYS_INLINE EnableIfFloatingPoint<RetType> remainder(EnableIfArithmetic<ValueType> x, ValueType y) noexcept { return std::remainder(x, y); }

		// Min - max - difference

		/**
		 * @brief Get the minimum between two numbers.
		 * @param x First number.
		 * @param y Second number.
		 * @return The minimum number.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> min(T x, T y) noexcept { return std::min(x, y); }

		/**
		 * @brief Get the maximum between two numbers.
		 * @param x First number.
		 * @param y Second number.
		 * @return The minimum number.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> max(T x, T y) noexcept { return std::max(x, y); }

		/**
		 * @brief Get the positive difference between two numbers.
		 * @param x First number.
		 * @param y Second number.
		 * @return abs(x - y).
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> positiveDifference(T x, T y) noexcept { return abs(x - y); }

		/**
		 * @brief Clamp value in range.
		 * @param x The value.
		 * @param min Minimum bound.
		 * @param max Maximum bound.
		 * @return Clamped value.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> clamp(T x, T minimum, T maximum) noexcept { return min(maximum, max(minimum, x)); }

		/**
		 * @brief Clamp value in range 0 to 1.
		 * @param x The value.
		 * @return Clamped value.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE EnableIfArithmetic<T> clamp01(T x) noexcept { return clamp<T>(x, 0, 1); }

		/**
		 * @brief Check if two numbers are approximately equal to each other.
		 * @param x First number.
		 * @param y Second number.
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE bool approximatelyEquals(EnableIfFloatingPoint<T> x, T y) noexcept { return positiveDifference(x, y) < epsilon(); }

		/**
		 * @brief Check if two numbers are approximately equal to each other provided a max treshold.
		 * @param x First number.
		 * @param y Second number.
		 * @param threshold Max threshold.
		 * @overload
		*/
		template <typename T = Float>
		static HNY_ALWAYS_INLINE bool approximatelyEquals(EnableIfFloatingPoint<T> x, T y, T threshold) noexcept { return positiveDifference(x, y) < threshold; }
	}

//#if !defined(HNY_STRICT_MATH_NAMESPACE)
	namespace Mathf = Math::Functions;
//#endif
}
