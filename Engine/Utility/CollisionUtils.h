#pragma once

#include "VectorUtils.h"

constexpr float LINE_LINE_PIXEL_DEFAULT_INCERTITUDE = 3.f;

class CollisionUtils
{
public:
	struct HitResult
	{
		sf::Vector2f impactPoint;
		sf::Vector2f normal;
		float depth;
	};


	static bool circleAboveMultiLines(const std::vector<sf::Vector2f>& allPoints, const sf::Vector2f& circlePos, const float circleRadius, HitResult& outHitResult)
	{
		sf::Vector2f impactPoint;

		for (int i = 0; i < static_cast<int>(allPoints.size()) - 1; ++i)
		{
			if(lineToCircle(allPoints[i].x, allPoints[i].y, allPoints[i + 1].x, allPoints[i + 1].y, circlePos.x, circlePos.y, circleRadius, impactPoint))
			{
				const auto hitLine = VectorUtils::GetDirectionVector(sf::Vector2f(allPoints[i + 1].x, allPoints[i + 1].y), sf::Vector2f(allPoints[i].x, allPoints[i].y));

				outHitResult.impactPoint = impactPoint;
				outHitResult.normal = VectorUtils::Normalize(VectorUtils::GetNormal(hitLine));

				return true;
			}
		}

		return false;
	}

	// Polygons to...
	static bool polygonToPolygon(const std::vector<sf::Vector2f>& verticesA, const std::vector<sf::Vector2f>& verticesB)
	{
		for (int j = 0; j < 2; ++j) // Looping through both of the polygons
		{
			const std::vector<sf::Vector2f>& currentPolygonVertices = j == 0 ? verticesA : verticesB;

			for (int i = 0; i < static_cast<int>(currentPolygonVertices.size()); ++i)
			{
				const auto va = currentPolygonVertices[i];
				const auto vb = currentPolygonVertices[(i + 1) % static_cast<int>(currentPolygonVertices.size())];

				const auto edge = vb - va;
				const auto axis = VectorUtils::GetNormal(edge); // Get normal of current edge for SAT

				float minA{ 0.f }, maxA{ 0.f }, minB{ 0.f }, maxB{ 0.f };

				ProjectVertices(verticesA, axis, minA, maxA);
				ProjectVertices(verticesB, axis, minB, maxB);

				if (minA >= maxB || minB >= maxA) // Gap found between polygon A and polygon B
				{
					return false;
				}
			}
		}

		return true;
	}

	// ---- Circle to...
	static bool circleToCircle(const sf::Vector2f& fromCirclePos, float fromCircleRad, const sf::Vector2f& toCirclePos, float toCircleRad, HitResult& hitResult)
	{
		const float distanceSqr = VectorUtils::DistanceSqr(fromCirclePos, toCirclePos);
		const float bothRadius = fromCircleRad + toCircleRad;
		const float bothRadiusSqr = bothRadius * bothRadius;

		if (distanceSqr <= bothRadiusSqr) // Using Sqr distance and squared radius to avoid heavy std::sqrt
		{
			const sf::Vector2f ab = toCirclePos - fromCirclePos;

			if(ab != VectorUtils::zero) // Center of the circle
			{
				hitResult.impactPoint = fromCirclePos + VectorUtils::Normalize(ab) * fromCircleRad;
				hitResult.normal = VectorUtils::Normalize(VectorUtils::GetDirectionVector(hitResult.impactPoint, fromCirclePos));
			}
			else
			{
				hitResult.impactPoint = fromCirclePos;
				hitResult.normal = VectorUtils::top;
			}

			hitResult.depth = bothRadiusSqr - distanceSqr;

			return true;
		}

		return false;
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

	static bool lineToPoint(float x1, float y1, float x2, float y2, float px, float py, float incertitude = LINE_LINE_PIXEL_DEFAULT_INCERTITUDE)
	{
		const float d1 = VectorUtils::Distance(sf::Vector2f(px, py), sf::Vector2f(x1, y1));
		const float d2 = VectorUtils::Distance(sf::Vector2f(px, py), sf::Vector2f(x2, y2));
		
		const float lineLength = VectorUtils::Distance(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2));

		// Since floats are so minutely accurate, add a little buffer zone that will give collision
		const float buffer = incertitude; // Higher = less accurate
		const float d1Andd2 = d1 + d2;

		return d1Andd2 >= lineLength - buffer && d1Andd2 <= lineLength + buffer;
	}

	static bool lineToCircle(float x1, float y1, float x2, float y2, float cX, float cY, float cR, sf::Vector2f& outImpactPoint)
	{
		const float lengthLine = VectorUtils::Distance(x1, y1, x2, y2);

		if (lengthLine < 0.000001f)
			return false; // Division by 0 guard

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

private:
	static void ProjectVertices(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis, float& min, float& max)
	{
		min = std::numeric_limits<float>::max();
		max = std::numeric_limits<float>::lowest();

		for (const auto& v : vertices)
		{
			const float proj = VectorUtils::Dot(v, axis);

			if (proj < min) 
				{ min = proj; }

			if (proj > max) 
				{ max = proj; }
		}
	}
};