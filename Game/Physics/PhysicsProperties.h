#pragma once

#include <algorithm>

// One pixel = one centimeter.
constexpr float PHYSICS_UNIT_METER_PER_PIXEL = 0.01f;

struct PhysicsProperties
{
public:
	PhysicsProperties() = default;

	PhysicsProperties(float density, float bounciness, bool isStatic = false, bool canBounceOff = true, float surfaceArea = 0.f) :
		m_density(density),
		m_mass{ surfaceArea * PHYSICS_UNIT_METER_PER_PIXEL * density },
		m_invMass(!isStatic ? 1 / m_mass : 0.f),
		m_bounciness(std::clamp(bounciness, 0.f, 1.f)),
		m_isStatic(isStatic),
		m_canBounceOff(canBounceOff)
	{ }

	/**
	 * World objects density table : https://www.thoughtco.com/table-of-densities-of-common-substances-603976
	 */
	float m_density{ 0.f };

	/**
	 * The mass of an object is auto-calculated, base of its area and PHYSICS_UNIT_METER_PER_PIXEL.
	 */
	float m_mass{ 0.f };

	/**
	 * Used for calculations.It is equal to 1 / m_mass.
	 * If it is static, it is equal to 0.
	 */
	float m_invMass{ 0.f };

	/**
	 * Bounciness factor. Or "restitution", physically speaking. From 0 to 1. 
	 * Amount of restitution force when colliding with an object
	 */
	float m_bounciness{ 0.f };

	/**
	 * The object will not be submitted by any forces but will have a restitution force.
	 */
	bool m_isStatic{ false };

	/**
	 * By default, objects can bounce off surfaces.
	 * Maybe some objects would become "static" when colliding with something, without any collision response.
	 */
	bool m_canBounceOff{ true };
};
