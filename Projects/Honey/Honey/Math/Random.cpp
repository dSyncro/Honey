#include "Random.h"

#include <Honey/Core/Assertion.h>

using namespace Honey;
using namespace Honey::Math;

bool Random::Bool()
{
	std::bernoulli_distribution dist = std::bernoulli_distribution();
	std::mt19937& mt = GetEngine();
	return dist(mt);
}

double Random::Double(double min, double max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_real_distribution<double> dist = std::uniform_real_distribution<double>(min, max);
	std::mt19937& mt = GetEngine();
	return dist(mt);
}

float Random::Float(float min, float max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_real_distribution<float> dist = std::uniform_real_distribution<float>(min, max);
	std::mt19937& mt = GetEngine();
	return dist(mt);
}

 int Random::Int(int min, int max)
{
	HNY_CORE_ASSERT(min < max, "min is > max");
	std::uniform_int_distribution<int> dist = std::uniform_int_distribution<int>(min, max);
	std::mt19937& mt = GetEngine();
	return dist(mt);
}