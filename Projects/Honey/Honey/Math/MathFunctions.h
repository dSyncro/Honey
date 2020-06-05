#pragma once

#include <cmath>
#include <limits>

namespace Honey {

	namespace Math::Functions {

		const float Pi = 3.14159265358979f;
		const float Degrees2Radians = (Pi * 2.0f) / 360.0f;
		const float Radians2Degrees = 360.0f / (Pi * 2.0f);

		const float Epsilon = std::numeric_limits<float>::epsilon();

		const float NaN = std::numeric_limits<float>::quiet_NaN();
		const float Infinity = std::numeric_limits<float>::infinity();
		const float NegativeInfinity = -std::numeric_limits<float>::infinity();

		inline float  Abs(float x) { return std::abs(x); }
		//inline double Abs(double x) { return std::abs(x); }

		inline int    Sign(int x) { return -(x < 0); }
		inline float  Sign(float x) { return (float)(-(x < 0)); }
		//inline double Sign(double x) { return (double)(-(x < 0)); }

		inline bool IsPowerOfTwo(int x) { return x & !(x & (x - 1)) && x >= 0; }
		inline bool IsPowerOfTwo(unsigned int x) { return x & !(x & (x - 1)); }

		// Trigonometry
		inline float  Cos(float x) { return std::cos(x); }
		//inline double Cos(double x) { return std::cos(x); }
		inline float  Sin(float x) { return std::sin(x); }
		//inline double Sin(double x) { return std::sin(x); }
		inline float  Tan(float x) { return std::tan(x); }
		//inline double Tan(double x) { return std::tan(x); }

		inline float  Acos(float x) { return std::acos(x); }
		//inline double Acos(double x) { return std::acos(x); }
		inline float  Asin(float x) { return std::asin(x); }
		//inline double Asin(double x) { return std::asin(x); }
		inline float  Atan(float x) { return std::atan(x); }
		//inline double Atan(double x) { return std::atan(x); }
		inline float  Atan2(float y, float x) { return std::atan2(y, x); }
		//inline double Atan2(double y, double x) { return std::atan2(y, x); }

		// Hyperbolic
		inline float  Cosh(float x) { return std::cosh(x); }
		//inline double Cosh(double x) { return std::cosh(x); }
		inline float  Sinh(float x) { return std::sinh(x); }
		//inline double Sinh(double x) { return std::sinh(x); }
		inline float  Tanh(float x) { return std::tanh(x); }
		//inline double Tanh(double x) { return std::tanh(x); }

		inline float  Acosh(float x) { return std::acosh(x); }
		//inline double Acosh(double x) { return std::acosh(x); }
		inline float  Asinh(float x) { return std::asinh(x); }
		//inline double Asinh(double x) { return std::asinh(x); }
		inline float  Atanh(float x) { return std::atanh(x); }
		//inline double Atanh(double x) { return std::atanh(x); }

		// Exponential and Logarithmic
		inline float  Exp(float x) { return std::exp(x); }
		//inline double Exp(double x) { return std::exp(x); }
		inline float  Exp2(float x) { return std::exp2(x); }
		//inline double Exp2(double x) { return std::exp2(x); }
		inline float  Ln(float x) { return std::log(x); }
		//inline double Ln(double x) { return std::log(x); }
		inline float  Log2(float x) { return std::log2(x); }
		//inline double Log2(double x) { return std::log2(x); }
		inline float  Log10(float x) { return std::log10(x); }
		//inline double Log10(double x) { return std::log10(x); }
		inline float  Log(float base, float x) { return Log2(x) / Log2(base); }
		//inline double Log(double base, double x) { return Log2(x) / Log2(base); }

		// Power
		inline float  Pow(float x, float y) { return std::pow(x, y); }
		//inline double Pow(double x, double y) { return std::pow(x, y); }
		inline float  Sqrt(float x) { return std::sqrt(x); }
		//inline double Sqrt(double x) { return std::sqrt(x); }
		inline float  Cbrt(float x) { return std::cbrt(x); }
		//inline double Cbrt(double x) { return std::cbrt(x); }

		// Rounding and remainder
		inline float  Ceil(float x) { return std::ceil(x); }
		//inline double Ceil(double x) { return std::ceil(x); }
		inline float  Floor(float x) { return std::floor(x); }
		//inline double Floor(double x) { return std::floor(x); }
		inline float  Truncate(float x) { return std::trunc(x); }
		//inline double Truncate(double x) { return std::trunc(x); }
		inline float  Mod(float x, float y) { return std::fmod(x, y); }
		//inline double Mod(double x, float y) { return std::fmod(x, y); }
		inline float  Remainder(float x, float y) { return std::remainder(x, y); }
		//inline double Remainder(double x, float y) { return std::remainder(x, y); }

		// Min - max - difference
		inline float  Min(float x, float y) { return std::fmin(x, y); }
		//inline double Min(double x, float y) { return std::fmin(x, y); }
		inline float  Max(float x, float y) { return std::fmax(x, y); }
		//inline double Max(double x, float y) { return std::fmax(x, y); }
		inline float  PositiveDifference(float x, float y) { return std::fdim(x, y); }
		//inline double PositiveDifference(double x, float y) { return std::fdim(x, y); }

		inline float  Clamp(float x, float min, float max) { return Min(max, Max(min, x)); }
		//inline double Clamp(double x, double min, double max) { return Min(max, Max(min, x)); }
		inline float  Clamp01(float x) { return Clamp(x, 0.0f, 1.0f); }
		//inline double Clamp01(double x) { return Clamp(x, 0.0, 1.0); }

		inline bool ApproximatelyEquals(float x, float y) { return PositiveDifference(x, y) < Epsilon; }
		//inline bool ApproximatelyEquals(double x, double y) { return PositiveDifference(x, y) < std::numeric_limits<double>::epsilon(); }
	}

	namespace Mathf = Math::Functions;
}