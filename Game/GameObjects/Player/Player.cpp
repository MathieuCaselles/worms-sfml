#include "Player.h"

Player::Player(const sf::CircleShape& circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	CircleRigidBody(circleShape, properties),
	m_playerShape(circleShape)
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_playerShape.setPosition(m_rbPosition);
}

const int& Player::getButtonState()
{
	return m_inputState;
}

void Player::setButtonState(input_states newState)
{
	m_inputState = newState;
}