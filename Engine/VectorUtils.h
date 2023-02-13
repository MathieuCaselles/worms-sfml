#pragma once

#include "MathUtils.h"

class VectorUtils
{
public:
    static float Dot(const sf::Vector2f& lhs, const sf::Vector2f& rhs)      { return lhs.x * rhs.x + lhs.y * rhs.y; }
    static float Distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return Magnitude(lhs - rhs); }
    static float Magnitude(const sf::Vector2f& vector)                      { return std::sqrt(Dot(vector, vector)); }
    static float SqrMagnitude(const sf::Vector2f& vector)                   { return Dot(vector, vector); }
    static sf::Vector2f Normalize(const sf::Vector2f& vector)               { return vector / Magnitude(vector); }

	static sf::Vector3f Cross(const sf::Vector3f& lhs, const sf::Vector3f& rhs)
    {
        return {
	        lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

    static float Cross(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

	static float GetAngle(const sf::Vector2f& from, const sf::Vector2f& to)
    {
        const float denominator = std::sqrt(SqrMagnitude(from) * SqrMagnitude(to));
        const float finalDot = std::clamp(Dot(from, to) / denominator, -1.f, 1.f);

        return std::acos(finalDot) * MathUtils::RAD_TO_DEG;
    }

	static sf::Vector2f Reflect(const sf::Vector2f& inDirection, const sf::Vector2f& inNormal)
    {
        const float factor = -2.f * Dot(inNormal, inDirection);
        return {
        	factor * inNormal.x + inDirection.x,
            factor * inNormal.y + inDirection.y
        };
    }
};