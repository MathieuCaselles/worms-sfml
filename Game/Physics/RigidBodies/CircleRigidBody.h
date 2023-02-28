#pragma once

#include <iostream>

#include "IRigidBody.h"
#include "SFML/Graphics/CircleShape.hpp"

struct PhysicsProperties;

class CircleRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(CircleRigidBody, IRigidBody)

public:
	CircleRigidBody(sf::CircleShape& circleShape, const PhysicsProperties& properties);
	CircleRigidBody(const CircleRigidBody& circleRb) = default;
	~CircleRigidBody() override = default;

	void step(const float& deltaTime) override;
	void updateMass() override;

	[[nodiscard]] float getRadius() const { return m_circleCollisionShape.getRadius(); }

private:
	sf::CircleShape& m_circleCollisionShape;
};
