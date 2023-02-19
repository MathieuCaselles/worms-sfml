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
	FallingCircle(const sf::Vector2f& initialPos, float radius, const sf::Color& color, const PhysicsProperties& properties);

	~FallingCircle() override = default;

private:
	sf::CircleShape m_circleShape;
};
