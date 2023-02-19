#pragma once

class MathUtils
{
public:
	constexpr static float PI = 3.14159265358979f;
	constexpr static float DEG_TO_RAD = PI * 2.f / 360.f;
	constexpr static float RAD_TO_DEG = 1.f / DEG_TO_RAD;

	static int getRandomNumber(int minRangeInclusive, int maxRangeInclusive);
};
