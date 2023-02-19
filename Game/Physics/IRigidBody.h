#pragma once

#include "PhysicsProperties.h"
#include "SFML/System/Vector2.hpp"

class IRigidBody
{
public:
	virtual ~IRigidBody() = default;

	virtual void step(const float& deltaTime);

	bool operator==(const IRigidBody& other) const
	{
		return m_rbPosition == other.m_rbPosition && m_rbVelocity == other.m_rbVelocity;
	}

	void setVelocity(const sf::Vector2f& velocity) { m_rbVelocity = velocity; }

protected:
	explicit IRigidBody(const PhysicsProperties& properties);

	sf::Vector2f m_rbPosition;
	sf::Vector2f m_rbVelocity;

	float m_rbRotation { 0.f };
	float m_rbAngularVelocity { 0.f };

	PhysicsProperties m_rbProperties;
};
