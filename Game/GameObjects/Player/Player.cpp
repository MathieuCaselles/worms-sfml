#include "Player.h"

#include <iostream>

const int& Player::getButtonState()
{
	return m_inputState;
}

void Player::setButtonState(input_states newState)
{
	m_inputState = newState;
}

bool Player::getCanPlay() const
{
	return m_canPlay;
}

void Player::setCanPlay(bool newBool)
{
	m_canPlay = newBool;
}

int Player::getHealth()
{
	return m_health;
}

void Player::setHealth(int newHealth)
{
	m_health = newHealth;
}

void Player::removeHealth(int healthRemoved)
{
	m_health -= healthRemoved;
	if (m_health <= 0)
	{
		std::cout << "Worm Dead" << std::endl;
	}
}

Player::Player(int health, const sf::CircleShape& circleShape, const PhysicsProperties& properties,
	const sf::Vector2f& initialPosition)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	CircleRigidBody(circleShape, properties),
	m_playerShape(circleShape), m_health(health)
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_playerShape.setPosition(m_rbPosition);
}