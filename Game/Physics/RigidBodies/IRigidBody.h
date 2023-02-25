#pragma once

#include <list>

#include "SFML/System/Vector2.hpp"

#include "Game/Physics/PhysicsProperties.h"
#include "Engine/Utility/RTTI.h"

class IRigidBody : public HasRTTI
{
public:
	DECLARE_RTTI(IRigidBody, NoRTTIRoot)

public:
	virtual ~IRigidBody() = default;
	virtual void step(const float& deltaTime);

	/**
	 * Depending of the area of the shape, you can override this method to change its mass.
	 * The inverse mass is updated by default. Consider doing this every time you override.
	 */
	virtual void updateMass();

	void addForce(const sf::Vector2f& force);
	void translate(const sf::Vector2f& movementVector);

	void setVelocity(const sf::Vector2f& velocity) { m_rbVelocity = velocity; }
	void setAngularVelocity(float angularVelocity) { m_rbAngularVelocity = angularVelocity; }

	[[nodiscard]] sf::Vector2f getPosition() const { return m_rbPosition; }
	[[nodiscard]] sf::Vector2f getVelocity() const { return m_rbVelocity; }
	[[nodiscard]] float getAngularVelocity() const { return m_rbAngularVelocity; }
	[[nodiscard]] PhysicsProperties getProperties() const { return m_rbProperties; }

	bool operator==(const IRigidBody& other) const
	{
		return m_rbPosition == other.m_rbPosition && m_rbVelocity == other.m_rbVelocity;
	}

	void tryOnCollisionEnter()
	{
		if(!m_isCurrentlyColliding)
		{
			m_isCurrentlyColliding = true;
			onCollisionEnter();
		}
	}

	void tryOnCollisionExit()
	{
		if (m_isCurrentlyColliding)
		{
			m_isCurrentlyColliding = false;
			onCollisionExit();
		}
	}

protected:
	explicit IRigidBody(const PhysicsProperties& properties);
	virtual void onCollisionEnter() {  }
	virtual void onCollisionExit() { }

	sf::Vector2f m_rbPosition;
	sf::Vector2f m_rbVelocity;

	float m_rbRotation { 0.f };
	float m_rbAngularVelocity { 0.f };

	std::list<sf::Vector2f> m_forces;

	PhysicsProperties m_rbProperties;

	bool m_isCurrentlyColliding;
};