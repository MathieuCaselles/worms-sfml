#pragma once

#include "GCFallingBox.h"
#include "PCFallingBox.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class FallingBoxRB : public Engine::GameObject<PCFallingBox, GCFallingBox, ICVoid>,
					 public BoxRigidBody
{
	friend PCFallingBox;
	friend GCFallingBox;

public:
	FallingBoxRB();
	FallingBoxRB(sf::RectangleShape rectangleShape, const PhysicsProperties& properties);
	FallingBoxRB(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	~FallingBoxRB() override = default;

private:
	sf::RectangleShape m_rectangleShape;
};
