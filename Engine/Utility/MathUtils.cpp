#include "MathUtils.h"

#include <random>

int MathUtils::getRandomNumber(int minRangeInclusive, int maxRangeInclusive)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> range(minRangeInclusive, maxRangeInclusive);

	return static_cast<int>(range(rng));
}

float MathUtils::convertKmPerHToMS(const float valueKmPerH)
{
	return valueKmPerH * 1000.f / 3600.f;
}
