#pragma once

#include "PhysicsProperties.h"
#include "SFML/System/Vector2.hpp"
#include "Engine/Utility/RTTI.h"

class IRigidBody : public HasRTTI
{
public:
	DECLARE_RTTI(IRigidBody, NoRTTIRoot)

public:
	virtual ~IRigidBody() = default;

	virtual void step(const float& deltaTime);

	bool operator==(const IRigidBody& other) const
	{
		return m_rbPosition == other.m_rbPosition && m_rbVelocity == other.m_rbVelocity;
	}

	void addForce(const sf::Vector2f& movement)
	{
		if(!m_rbProperties.m_isStatic)
			m_rbPosition += movement;
	}

	void setVelocity(const sf::Vector2f& velocity) { m_rbVelocity = velocity; }

	sf::Vector2f getPosition() const { return m_rbPosition; }
	sf::Vector2f getVelocity() const { return m_rbVelocity; }
	PhysicsProperties getProperties() const { return m_rbProperties; }

protected:
	explicit IRigidBody(const PhysicsProperties& properties);

	sf::Vector2f m_rbPosition;
	sf::Vector2f m_rbVelocity;

	float m_rbRotation { 0.f };
	float m_rbAngularVelocity { 0.f };

	PhysicsProperties m_rbProperties;
};
