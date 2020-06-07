#pragma once

#include <random>

namespace Honey::Math {

	class Random {

		Random() = delete;
		Random(Random&&) = delete;
		Random(const Random&) = delete;
		Random& operator =(Random&&) = delete;
		Random& operator =(const Random&) = delete;

		/**
		 * Generate a random bool value.
		 * @return Either true or false.
		 */
		static bool Bool();

		/**
		 * Generate a random double.
		 * @return A random double between 0 and 1.
		 */
		static double Double() { return Double(0, 1); }

		/**
		 * Generate a random double.
		 * @param max The maximum number to be generated.
		 * @return A random double between 0 (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static double Double(double max) { return Double(0, max); }

		/**
		 * Generate a random double.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random double between `min` (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static double Double(double min, double max);

		/**
		 * Generate a random float.
		 * @return A random float between 0 and 1.
		 */
		static float Float() { return Float(0, 1); }

		/**
		 * Generate a random float.
		 * @param max The maximum number to be generated.
		 * @return A random float between 0 (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static float Float(float max) { return Float(0, max); }

		/**
		 * Generate a random float.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random float between `min` (inclusive) and `max` (exclusive).
		 * @overload
		 */
		static float Float(float min, float max);

		/**
		 * Generate a random integer.
		 * @return A random integer between 0 and int max value.
		 */
		static int Int() { return Int(0, (std::numeric_limits<int>::max)()); }

		/**
		 * Generate a random integer.
		 * @param max The maximum number to be generated.
		 * @return A random integer between 0 (inclusive) and `max` (inclusive).
		 * @overload
		 */
		static int Int(int max) { return Int(0, max); }

		/**
		 * Generate a random integer.
		 * @param min The minimum number to be generated.
		 * @param max The maximum number to be generated.
		 * @return A random integer between `min` (inclusive) and `max` (inclusive).
		 * @overload
		 */
		static int Int(int min, int max);

	private:

		inline static std::mt19937& GetEngine()
		{
			static std::random_device seed_gen;
			static std::mt19937 engine(seed_gen());
			return engine;
		}
	};

}