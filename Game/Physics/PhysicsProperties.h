#pragma once

#include <algorithm>

struct PhysicsProperties
{
public:
	PhysicsProperties() = default;

	PhysicsProperties(float density, float bounciness, bool isStatic = false, bool canBounceOff = true, float surfaceArea = 0.f) :
		m_density(density),
		m_mass{ surfaceArea * density },
		m_invMass(!isStatic ? 1 / (surfaceArea * density) : 0.f),
		m_bounciness(std::clamp(bounciness, 0.f, 1.f)),
		m_isStatic(isStatic),
		m_canBounceOff(canBounceOff)
	{ }

	float m_density{ 0.f };
	float m_mass{ 0.f };
	float m_invMass{ 0.f };
	float m_bounciness{ 0.f };

	bool m_isStatic{ false };

	/**
	 * By default, objects can bounce off surfaces.
	 * Maybe some would become like static when colliding with something, without any collision response.
	 */
	bool m_canBounceOff{ true };
};
