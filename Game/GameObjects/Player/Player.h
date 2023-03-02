#pragma once

#include "GCPlayer.h"
#include "PCPlayer.h"
#include "ICPlayer.h"

#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"

enum input_states { IDLE, RIGHT, LEFT, JUMP, CLICK };
enum skill_states { GRENADE, BANANA, BLACK_HOLE };

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

	const bool getCanPlay();
	void setCanPlay(bool newBool);

	int getHealth();
	void setHealth(int newHealth);
	void removeHealth(int healthRemoved);

	void setSkillState(skill_states newState);

private:
	Player();
	Player(sf::CircleShape circleShape, const PhysicsProperties& properties);
	Player(int health,sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation = 0.f);

	sf::CircleShape m_circleShape;
	bool m_canPlay = false;
	input_states m_inputState;
	skill_states m_skillState;

	float m_movement = 150.f;

	int m_health;
};