#pragma once

#include "VectorUtils.h"

class CollisionUtils
{
public:
	static bool collisionPointToTriangle(const sf::Vector2f& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
	{
		const sf::Vector2f ab = b - a;
		const sf::Vector2f bc = c - b;
		const sf::Vector2f ca = a - c;

		const sf::Vector2f ap = point - a;
		const sf::Vector2f bp = point - b;
		const sf::Vector2f cp = point - c;

		const float cross1 = VectorUtils::Cross(ab, ap);
		const float cross2 = VectorUtils::Cross(bc, bp);
		const float cross3 = VectorUtils::Cross(ca, cp);

		return cross1 < 0.f && cross2 < 0.f && cross3 < 0.f;
	}
};