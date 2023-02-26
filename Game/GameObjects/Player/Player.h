#pragma once

#include "GCPlayer.h"
#include "PCPlayer.h"
#include "ICPlayer.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"


class Player : public Engine::GameObject<PCPlayer, GCPlayer, ICPlayer>, 
				public BoxRigidBody
{
	friend PCPlayer;
	friend GCPlayer;
	friend ICPlayer;

public:
	Player();
	Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties);
	Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);
	~Player() override = default;

private:
	sf::RectangleShape m_rectangleShape;
};