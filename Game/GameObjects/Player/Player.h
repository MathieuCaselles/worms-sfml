#pragma once

#include "GCPlayer.h"
#include "PCPlayer.h"
#include "ICPlayer.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

enum input_states { BUTTON, BUTTON_RIGHT, BUTTON_LEFT, BUTTON_JUMP, BUTTON_LEFTCLICK };

class Player : public Engine::GameObject<PCPlayer, GCPlayer, ICPlayer>, 
				public BoxRigidBody
{
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;

	friend PCPlayer;
	friend GCPlayer;
	friend ICPlayer;

public:
	Player();
	Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties);
	Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);
	~Player() override = default;

	const int& getButtonState();
	virtual void setButtonState(input_states new_state);

private:
	sf::RectangleShape m_rectangleShape;

	input_states m_inputState;
};