#pragma once

#include "GCPlayer.h"
#include "PCPlayer.h"
#include "ICPlayer.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"

enum input_states { BUTTON, BUTTON_RIGHT, BUTTON_LEFT, BUTTON_JUMP, BUTTON_LEFTCLICK };

class Player : public Engine::GameObject<PCPlayer, GCPlayer, ICPlayer>, 
				public CircleRigidBody
{
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;

	friend PCPlayer;
	friend GCPlayer;
	friend ICPlayer;

public:
	~Player() override = default;

	const int& getButtonState();
	virtual void setButtonState(input_states new_state);


private:
	Player();
	Player(sf::CircleShape circleShape, const PhysicsProperties& properties);
	Player(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	sf::CircleShape m_circleShape;

	input_states m_inputState;
};