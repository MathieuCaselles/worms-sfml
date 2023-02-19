#pragma once

#include <algorithm>

struct PhysicsProperties
{
public:
	PhysicsProperties() = default;

	PhysicsProperties(float density, float bounciness, bool isStatic = false, float surfaceArea = 0.f) :
		m_density(density),
		m_mass{ surfaceArea * density },
		m_bounciness(std::clamp(bounciness, 0.f, 1.f)),
		m_isStatic(isStatic)
	{ }

	float m_density{ 0.f };
	float m_mass{ 0.f };
	float m_bounciness{ 0.f };

	bool m_isStatic{ false };
};
