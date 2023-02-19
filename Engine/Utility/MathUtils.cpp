#include "MathUtils.h"

#include <random>

int MathUtils::getRandomNumber(int minRangeInclusive, int maxRangeInclusive)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	const std::uniform_int_distribution<std::mt19937::result_type> range(minRangeInclusive, maxRangeInclusive);

	return static_cast<int>(range(rng)) + 1;
}