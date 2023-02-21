#pragma once

#include "Game/Physics/RigidBodies/IRigidBody.h"

#include "SFML/Graphics/CircleShape.hpp"

struct PhysicsProperties;

class CircleRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(CircleRigidBody, IRigidBody)

public:
	CircleRigidBody(sf::CircleShape& circleShape, const PhysicsProperties& properties);
	~CircleRigidBody() override = default;

	void step(const float& deltaTime) override;

	[[nodiscard]] float getRadius() const { return m_circleShape.getRadius(); }

private:
	sf::CircleShape& m_circleShape;
};
