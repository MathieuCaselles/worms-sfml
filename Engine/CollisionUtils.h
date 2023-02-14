#pragma once

#include "VectorUtils.h"

class CollisionUtils
{
public:
	// ---- Points to...
	static bool pointToCircle(float px, float py, float cx, float cy, float r)
	{
		return VectorUtils::Distance(px, py, cx, cy) <= r;
	}

	static bool pointToTriangle(const sf::Vector2f& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
	{
		const sf::Vector2f ab = b - a;
		const sf::Vector2f bc = c - b;
		const sf::Vector2f ca = a - c;

		const sf::Vector2f ap = point - a;
		const sf::Vector2f bp = point - b;
		const sf::Vector2f cp = point - c;

		const float cross1 = VectorUtils::Cross2D(ab, ap);
		const float cross2 = VectorUtils::Cross2D(bc, bp);
		const float cross3 = VectorUtils::Cross2D(ca, cp);

		return cross1 < 0.f && cross2 < 0.f && cross3 < 0.f;
	}

	// ---- Lines to...
	static bool lineToLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, sf::Vector2f& outIntersectionPoint)
	{
		// calculate the distance to intersection point
		const float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
		const float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

		// if uA and uB are between 0-1, lines are colliding
		if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
		{
			outIntersectionPoint.x = x1 + uA * (x2 - x1);
			outIntersectionPoint.y = y1 + uA * (y2 - y1);
			return true;
		}

		return false;
	}

	static bool lineToPoint(float x1, float y1, float x2, float y2, float px, float py)
	{
		const float d1 = VectorUtils::Distance(px, py, x1, y1);
		const float d2 = VectorUtils::Distance(px, py, x2, y2);

		const float lineLength = VectorUtils::Distance(x1, y1, x2, y2);

		// Since floats are so minutely accurate, add a little buffer zone that will give collision
		constexpr float buffer = 20.f; // Higher = less accurate

		return d1 + d2 >= lineLength - buffer && d1 + d2 <= lineLength + buffer;
	}

	static bool lineToCircle(float x1, float y1, float x2, float y2, float cX, float cY, float cR, sf::Vector2f& outImpactPoint)
	{
		const float lengthLine = VectorUtils::Distance(x1, y1, x2, y2);
		const float dot = ((cX - x1) * (x2 - x1) + (cY - y1) * (y2 - y1)) / (lengthLine * lengthLine);

		const float closestX = x1 + (dot * (x2 - x1));
		const float closestY = y1 + (dot * (y2 - y1));

		if (!lineToPoint(x1, y1, x2, y2, closestX, closestY)) return false;

		if (pointToCircle(closestX, closestY, cX, cY, cR))
		{
			outImpactPoint.x = closestX;
			outImpactPoint.y = closestY;
			return true;
		}

		return false;
	}
};