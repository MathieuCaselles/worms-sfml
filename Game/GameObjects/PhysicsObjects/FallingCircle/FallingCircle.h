#pragma once

#include "GCFallingCircle.h"
#include "PCFallingCircle.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class FallingCircle : public Engine::GameObject<PCFallingCircle, GCFallingCircle, ICVoid>,
                        public CircleRigidBody
{
	friend PCFallingCircle;
	friend GCFallingCircle;

public:
	FallingCircle();

	// The initial position will be the position from circleShape.getPosition()
	FallingCircle(const sf::CircleShape& circleShape, const PhysicsProperties& properties);

	// The initial position will be the parameter initialPosition
	FallingCircle(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	~FallingCircle() override = default;

	[[nodiscard]] const sf::CircleShape& getCircleShape() const { return m_circleShape; }

private:
	sf::CircleShape m_circleShape;
};
