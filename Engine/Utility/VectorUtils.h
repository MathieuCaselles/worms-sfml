#pragma once

#include <string>

#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"

class VectorUtils
{
public:
    inline static sf::Vector2f zero   = sf::Vector2f(0, 0);
    inline static sf::Vector2f top    = sf::Vector2f(0, 1);
    inline static sf::Vector2f right  = sf::Vector2f(1, 0);
    inline static sf::Vector2f bottom = sf::Vector2f(0, -1);
    inline static sf::Vector2f left   = sf::Vector2f(-1, 0);

    static sf::Vector2f GetDirectionVector(const sf::Vector2f& pointA, const sf::Vector2f& pointB);

    static float Dot(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

    static float Distance(const float& aX, const float& aY, const float& bX, const float& bY);
    static float Distance(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
    static float DistanceSqr(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

    static float Magnitude(const sf::Vector2f& vector);
    static float SqrMagnitude(const sf::Vector2f& vector);

    static sf::Vector2f GetNormal(const sf::Vector2f& vector);

    static sf::Vector2f Normalize(const sf::Vector2f& vector);

    static sf::Vector2f Rotate(const sf::Vector2f vector, float angle);

    static float Cross2D(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
    static sf::Vector3f Cross3D(const sf::Vector3f& lhs, const sf::Vector3f& rhs);

    // Returned angle is always positive
    static float GetAngle(const sf::Vector2f& from, const sf::Vector2f& to);

    static sf::Vector2f ReflectOnSurface(const sf::Vector2f& direction, const sf::Vector2f& surface);

    static sf::Vector2f Reflect(const sf::Vector2f& direction, const sf::Vector2f& normal);

    static std::string ToString(const sf::Vector2f& vector);
};
