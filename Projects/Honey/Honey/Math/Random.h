#pragma once

#include <random>
#include <Honey/Core/TypeTraits.h>

namespace Honey::Math {

	/**
	 * @brief Generate random numbers easily.
	*/
	class Random {

		Random() = delete;
		Random(Random&&) = delete;
		Random(const Random&) = delete;
		Random& operator =(Random&&) = delete;
		Random& operator =(const Random&) = delete;

		/**
		 * Generate a random bool value.
		 * @param probability -> Probability of retrieving True.
		 * @return Either true or false depending on given probability.
		 */
		static bool generateBool(Float probability = 0.5f);

		/**
		 * Generate a random double.
		 * @return A random double between 0 and 1.
		 */
		static Double generateDouble() { return generateDouble(0.0, 1.0); }

		/**
		 * Generate a random double.
		 * @param max The maximum number to be generated.
		 * @return A random double between 0 (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static Double generateDouble(Double max) { return generateDouble(0.0, max); }

		/**
		 * Generate a random double.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random double between `min` (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static Double generateDouble(Double min, Double max);

		/**
		 * Generate a random float.
		 * @return A random float between 0 and 1.
		 */
		static Float generateFloat() { return generateFloat(0.0f, 1.0f); }

		/**
		 * Generate a random float.
		 * @param max The maximum number to be generated.
		 * @return A random float between 0 (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static Float generateFloat(Float max) { return generateFloat(0.0f, max); }

		/**
		 * Generate a random float.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random float between `min` (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static Float generateFloat(Honey::Float min, Honey::Float max);

		/**
		 * Generate a random integer.
		 * @return A random integer between 0 and int max value.
		 */
		static Int generateInt() { return generateInt(0, maxValue<Int>()); }

		/**
		 * Generate a random integer.
		 * @param max The maximum number to be generated.
		 * @return A random integer between 0 (inclusive) and `max` (inclusive).
		 * @overload
		 */
		static Int generateInt(Int max) { return generateInt(0, max); }

		/**
		 * Generate a random integer.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random integer between `min` (inclusive) and `max` (inclusive).
		 * @overload
		 */
		static Int generateInt(Int min, Int max);

	private:

		inline static std::mt19937& getEngine()
		{
			static std::random_device seed_gen;
			static std::mt19937 engine(seed_gen());
			return engine;
		}
	};

}
