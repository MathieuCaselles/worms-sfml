#pragma once

#include "MathUtils.h"

class VectorUtils
{
public:
    static sf::Vector2f GetDirectionVector(const sf::Vector2f& pointA, const sf::Vector2f& pointB) { return { pointB.x - pointA.x, pointB.y - pointA.y }; }

    static float Dot(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }    

    static float Distance(const float& aX, const float& aY, const float& bX, const float& bY) { return Distance(sf::Vector2f(aX, aY), sf::Vector2f(bX, bY)); }
    static float Distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs)                   { return Magnitude(lhs - rhs); }
    static float DistanceSqr(const sf::Vector2f& lhs, const sf::Vector2f& rhs)                { return SqrMagnitude(lhs - rhs); }

    static float Magnitude(const sf::Vector2f& vector)    { return std::sqrt(Dot(vector, vector)); }
    static float SqrMagnitude(const sf::Vector2f& vector) { return Dot(vector, vector); }

    static sf::Vector2f GetNormal(const sf::Vector2f& vector) { return { -vector.y, vector.x }; }

    static sf::Vector2f Normalize(const sf::Vector2f& vector) { return vector / Magnitude(vector); }

    static sf::Vector2f Rotate(const sf::Vector2f vector, float angle)
    {
        return {
            vector.x * std::cosf(angle) - vector.y * std::sinf(angle),
            vector.x * std::sinf(angle) + vector.y * std::cosf(angle)
        };
    }

    static float Cross2D(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
	static sf::Vector3f Cross3D(const sf::Vector3f& lhs, const sf::Vector3f& rhs)
    {
        return {
        	lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x };
    }

    // Returned angle is always positive
	static float GetAngle(const sf::Vector2f& from, const sf::Vector2f& to)
    {
        const float denominator = std::sqrt(SqrMagnitude(from) * SqrMagnitude(to));
        const float finalDot = std::clamp(Dot(from, to) / denominator, -1.f, 1.f);

        return std::acos(finalDot) * MathUtils::RAD_TO_DEG;
    }

    static sf::Vector2f ReflectOnSurface(const sf::Vector2f& direction, const sf::Vector2f& surface)
    {
       return Reflect(direction, GetNormal(surface));
    }

	static sf::Vector2f Reflect(const sf::Vector2f& direction, const sf::Vector2f& normal)
    {
        const float factor = -2.f * Dot(normal, direction);
        return {
        	factor * normal.x + direction.x,
            factor * normal.y + direction.y
        };
    }
};