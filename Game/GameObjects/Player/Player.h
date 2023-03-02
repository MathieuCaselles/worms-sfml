#pragma once

#include "GCPlayer.h"
#include "PCPlayer.h"
#include "ICPlayer.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"

enum input_states { IDLE, RIGHT, LEFT, JUMP, CLICK };

class Player : public Engine::GameObject<PCPlayer, GCPlayer, ICPlayer>, 
				public CircleRigidBody
{
public:
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;

	friend PCPlayer;
	friend GCPlayer;
	friend ICPlayer;

	~Player() override = default;

	const int& getButtonState();
	virtual void setButtonState(input_states new_state);

	bool getCanPlay() const;
	void setCanPlay(bool newBool);

	int getHealth();
	void setHealth(int newHealth);
	void removeHealth(int healthRemoved);
private:
	Player(int health, const sf::CircleShape& circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition);

	sf::CircleShape m_playerShape;
	bool m_canPlay = false;
	input_states m_inputState;

	float m_movementSpeed{ 150.f };

	int m_health;
};
