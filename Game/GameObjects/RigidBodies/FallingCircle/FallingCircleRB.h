#pragma once

#include "GCFallingCircle.h"
#include "PCFallingCircle.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class FallingCircleRB : public Engine::GameObject<PCFallingCircle, GCFallingCircle, ICVoid>,
                        public CircleRigidBody
{
	friend PCFallingCircle;
	friend GCFallingCircle;

public:
	FallingCircleRB();

	// The initial position will be the position from circleShape.getPosition()
	FallingCircleRB(sf::CircleShape circleShape, const PhysicsProperties& properties);

	// The initial position will be the parameter initialPosition
	FallingCircleRB(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	~FallingCircleRB() override = default;

	[[nodiscard]] const sf::CircleShape& getCircleShape() const { return m_circleShape; }

private:
	sf::CircleShape m_circleShape;
};
