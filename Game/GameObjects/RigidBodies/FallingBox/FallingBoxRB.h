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
	FallingBoxRB(const sf::Vector2f& initialPos, const sf::Vector2f& size, const sf::Color& color, const PhysicsProperties& properties);

	~FallingBoxRB() override = default;

private:
	sf::RectangleShape m_rectangleShape;
};
