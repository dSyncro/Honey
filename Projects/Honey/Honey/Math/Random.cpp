#include "Random.h"

#include <Honey/Core/Assertion.h>

using namespace Honey;
using namespace Honey::Math;

bool Random::generateBool(Float probability)
{
	HNY_CORE_ASSERT(probability <= 1.0f, "Probability is greater than 1.0");
	std::bernoulli_distribution dist = std::bernoulli_distribution(probability);
	std::mt19937& mt = getEngine();
	return dist(mt);
}

Double Random::generateDouble(Double min, Double max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_real_distribution<Double> dist = std::uniform_real_distribution<Double>(min, max);
	std::mt19937& mt = getEngine();
	return dist(mt);
}

Float Random::generateFloat(Float min, Float max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_real_distribution<Float> dist = std::uniform_real_distribution<Float>(min, max);
	std::mt19937& mt = getEngine();
	return dist(mt);
}

Int Random::generateInt(Int min, Int max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(min, max);
	std::mt19937& mt = getEngine();
	return dist(mt);
}
