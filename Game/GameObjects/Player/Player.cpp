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

void Player::setSkillState(skill_states newState)
{
	m_skillState = newState;
}

const skill_states Player::getSkillState() const
{
	return m_skillState;
}

void Player::setNumberBanana(int number)
{
	m_numberBanana = number;
}

void Player::setNumberBlackHole(int number)
{
	m_numberBlackHole = number;
}

const int Player::getNumberBanana() const
{
	return m_numberBanana;
}

const int Player::getNumberBlackHole() const
{
	return m_numberBlackHole;
}


Player::Player(int health, const sf::CircleShape& circleShape, const PhysicsProperties& properties,
	const sf::Vector2f& initialPosition)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	CircleRigidBody(circleShape, properties),
	m_playerShape(circleShape), m_health(health),
	m_numberBanana(1), m_numberBlackHole(1), m_inputState(IDLE), m_skillState(GRENADE)
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_playerShape.setPosition(m_rbPosition);
}