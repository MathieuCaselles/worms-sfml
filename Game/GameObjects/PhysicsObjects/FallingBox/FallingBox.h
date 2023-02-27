#pragma once

#include "GCFallingBox.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Components/PhysicsComponents/PCVoid.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class FallingBox : public Engine::GameObject<PCVoid, GCFallingBox, ICVoid>,
					 public BoxRigidBody
{
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCFallingBox;


private: 
	FallingBox();
	FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties);
	FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

public:
	~FallingBox() override = default;

private:
	sf::RectangleShape m_rectangleShape;
};
