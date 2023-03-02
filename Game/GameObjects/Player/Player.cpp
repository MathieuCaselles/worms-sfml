#include "Player.h"

#include <iostream>

Player::Player()
	: Player(sf::CircleShape(), {})
{ }

Player::Player(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Player(m_health,std::move(circleShape), properties, circleShape.getPosition(), circleShape.getRotation())
{ }

Player::Player(int health,sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	CircleRigidBody(m_circleShape, properties),
	m_circleShape(std::move(circleShape)), m_health(health)
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;
	m_rbRotation = initialRotation;

	m_circleShape.setPosition(m_rbPosition);
	m_circleShape.setRotation(m_rbRotation);
}

const int& Player::getButtonState()
{
	return m_inputState;
}

void Player::setButtonState(input_states newState)
{
	m_inputState = newState;
}

const bool Player::getCanPlay()
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

void Player::setSkillState(skill_states newState)
{
	m_skillState = newState;
}



