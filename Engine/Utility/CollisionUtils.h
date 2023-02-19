#pragma once

#include <vector>

#include "SFML/System/Vector2.hpp"

constexpr float LINE_LINE_PIXEL_DEFAULT_INCERTITUDE = 3.f;

class CollisionUtils
{
public:
	struct HitResult
	{
		bool hasHit { false };
		sf::Vector2f impactPoint;
		sf::Vector2f normal;
		float depth { 0.f };
	};

	static bool circleAboveMultiLines(const std::vector<sf::Vector2f>& allPoints, const sf::Vector2f& circlePos, const float circleRadius, HitResult& outHitResult);

	// Polygons to...
	static bool polygonToPolygon(const std::vector<sf::Vector2f>& verticesA, const std::vector<sf::Vector2f>& verticesB, HitResult& outHitResult);

	static bool polygonToCircle(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& circlePos, float circleRadius, HitResult& outHitResult);

	// ---- Circle to...
	static bool circleToCircle(const sf::Vector2f& fromCirclePos, float fromCircleRad, const sf::Vector2f& toCirclePos, float toCircleRad, HitResult& outHitResult);

	static bool circleToPolygon(const sf::Vector2f& circlePos, float circleRadius, const std::vector<sf::Vector2f>& vertices, HitResult& outHitResult);

	// ---- Lines to...
	static bool lineToLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, sf::Vector2f& outIntersectionPoint);

	static bool lineToPoint(float x1, float y1, float x2, float y2, float px, float py, float incertitude = LINE_LINE_PIXEL_DEFAULT_INCERTITUDE);

	static bool lineToCircle(float x1, float y1, float x2, float y2, float cX, float cY, float cR, sf::Vector2f& outImpactPoint);

	// ---- Points to...
	static bool pointToCircle(float px, float py, float cx, float cy, float r);

	static bool pointToTriangle(const sf::Vector2f& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c);

private:
	static void projectVertices(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& axis, float& min, float& max);
	static void projectCircle(const sf::Vector2f& circlePos, float circleRad, const sf::Vector2f& axis, float& min, float& max);

	static sf::Vector2f getClosestPolygonPointFromCircle(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& circlePos);
};