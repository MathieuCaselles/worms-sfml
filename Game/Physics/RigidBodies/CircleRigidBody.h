#pragma once

#include "Game/Physics/IRigidBody.h"
#include "SFML/Graphics/CircleShape.hpp"

class CircleRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(CircleRigidBody, IRigidBody)

public:
	CircleRigidBody(sf::CircleShape& circleShape, const PhysicsProperties& properties);
	~CircleRigidBody() override = default;

	void step(const float& deltaTime) override;
	[[nodiscard]] const sf::CircleShape& getCircleShape() const { return m_circleShape; }

private:
	sf::CircleShape& m_circleShape;
};