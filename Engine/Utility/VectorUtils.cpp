#include "VectorUtils.h"

#include <algorithm>
#include <complex>

#include "MathUtils.h"

sf::Vector2f VectorUtils::GetDirectionVector(const sf::Vector2f& pointA, const sf::Vector2f& pointB) { return { pointB.x - pointA.x, pointB.y - pointA.y }; }

float VectorUtils::Dot(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return lhs.x * rhs.x + lhs.y * rhs.y; }

float VectorUtils::Distance(const float& aX, const float& aY, const float& bX, const float& bY) { return Distance(sf::Vector2f(aX, aY), sf::Vector2f(bX, bY)); }
float VectorUtils::Distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return Magnitude(lhs - rhs); }
float VectorUtils::DistanceSqr(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return SqrMagnitude(lhs - rhs); }

float VectorUtils::Magnitude(const sf::Vector2f& vector) { return std::sqrt(Dot(vector, vector)); }
float VectorUtils::SqrMagnitude(const sf::Vector2f& vector) { return Dot(vector, vector); }

sf::Vector2f VectorUtils::GetNormal(const sf::Vector2f& vector) { return { -vector.y, vector.x }; }

sf::Vector2f VectorUtils::Normalize(const sf::Vector2f& vector) { return vector / Magnitude(vector); }

sf::Vector2f VectorUtils::Rotate(const sf::Vector2f vector, float angle)
{
    return {
        vector.x * std::cosf(angle) - vector.y * std::sinf(angle),
        vector.x * std::sinf(angle) + vector.y * std::cosf(angle)
    };
}

float VectorUtils::Cross2D(const sf::Vector2f& lhs, const sf::Vector2f& rhs) { return lhs.x * rhs.y - lhs.y * rhs.x; }
sf::Vector3f VectorUtils::Cross3D(const sf::Vector3f& lhs, const sf::Vector3f& rhs)
{
    return {
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x };
}

float VectorUtils::GetAngle(const sf::Vector2f& from, const sf::Vector2f& to)
{
    const float denominator = std::sqrt(SqrMagnitude(from) * SqrMagnitude(to));
    const float finalDot = std::clamp(Dot(from, to) / denominator, -1.f, 1.f);

    return std::acos(finalDot) * MathUtils::RAD_TO_DEG;
}

sf::Vector2f VectorUtils::ReflectOnSurface(const sf::Vector2f& direction, const sf::Vector2f& surface)
{
    return Reflect(direction, GetNormal(surface));
}

sf::Vector2f VectorUtils::Reflect(const sf::Vector2f& direction, const sf::Vector2f& normal)
{
    const float factor = -2.f * Dot(normal, direction);
    return {
        factor * normal.x + direction.x,
        factor * normal.y + direction.y
    };
}

std::string VectorUtils::ToString(const sf::Vector2f& vector)
{
    return "(" + std::to_string(vector.x) + ";" + std::to_string(vector.y) + ")";
}