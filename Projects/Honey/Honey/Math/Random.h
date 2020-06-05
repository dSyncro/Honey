#pragma once

#include <random>

namespace Honey::Math {

	class Random {

		Random() = delete;
		Random(Random&&) = delete;
		Random(const Random&) = delete;
		Random& operator =(Random&&) = delete;
		Random& operator =(const Random&) = delete;

		static bool Bool();

		static double Double() { return Double(0, 1); }
		static double Double(double max) { return Double(0, max); }
		static double Double(double min, float max);

		static float Float() { return Float(0, 1); }
		static float Float(float max) { return Float(0, max); }
		static float Float(float min, float max);

		static int Int() { return Int(0, (std::numeric_limits<int>::max)()); }
		static int Int(int max) { return Int(0, max); }
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