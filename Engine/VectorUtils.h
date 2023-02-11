#pragma once

class MathUtils
{
public:
    constexpr static float PI = 3.14159265358979f;
	constexpr static float DEG_TO_RAD = PI * 2.f / 360.f;
    constexpr static float RAD_TO_DEG = 1.f / DEG_TO_RAD;

    static void  Normalize(sf::Vector3f& vector)                            { vector = vector / Magnitude(vector); }
    static float Dot(const sf::Vector3f& lhs, const sf::Vector3f& rhs)      { return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z; }
    static float Distance(const sf::Vector3f& lhs, const sf::Vector3f& rhs) { return Magnitude(lhs - rhs); }
    static float Magnitude(const sf::Vector3f& vector)                      { return std::sqrt(Dot(vector, vector)); }
    static float SqrMagnitude(const sf::Vector3f& vector)                   { return Dot(vector, vector); }

	static sf::Vector3f Cross(const sf::Vector3f& lhs, const sf::Vector3f& rhs)
    {
        return {
	        lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

	static float GetAngle(const sf::Vector3f& from, const sf::Vector3f& to)
    {
        const float denominator = std::sqrt(SqrMagnitude(from) * SqrMagnitude(to));
        const float finalDot = std::clamp(Dot(from, to) / denominator, -1.f, 1.f);

        return std::acos(finalDot) * RAD_TO_DEG;
    }

	static sf::Vector3f Reflect(const sf::Vector3f& inDirection, const sf::Vector3f& inNormal)
    {
        const float factor = -2.f * Dot(inNormal, inDirection);
        return {
        	factor * inNormal.x + inDirection.x,
            factor * inNormal.y + inDirection.y,
            factor * inNormal.z + inDirection.z
        };
    }
};