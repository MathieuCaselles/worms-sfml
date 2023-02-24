#pragma once

#include "GCFallingBox.h"
#include "PCFallingBox.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class FallingBox : public Engine::GameObject<PCFallingBox, GCFallingBox, ICVoid>,
					 public BoxRigidBody
{
	friend PCFallingBox;
	friend GCFallingBox;

public:
	FallingBox();
	FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties);
	FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	~FallingBox() override = default;

private:
	sf::RectangleShape m_rectangleShape;
};
