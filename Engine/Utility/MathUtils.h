#pragma once

#include <random>

class MathUtils
{
public:
	constexpr static float PI = 3.14159265358979f;
	constexpr static float DEG_TO_RAD = PI * 2.f / 360.f;
	constexpr static float RAD_TO_DEG = 1.f / DEG_TO_RAD;

	static int getRandomNumber(int minRangeInclusive, int maxRangeInclusive)
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		const std::uniform_int_distribution<std::mt19937::result_type> range(minRangeInclusive, maxRangeInclusive);

		return static_cast<int>(range(rng)) + 1;
	}
};
