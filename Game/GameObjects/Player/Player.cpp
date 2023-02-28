#include "Player.h"

#include <iostream>

Player::Player()
	: Player(sf::CircleShape(), {})
{ }

Player::Player(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Player(std::move(circleShape), properties, circleShape.getPosition(), circleShape.getRotation())
{ }

Player::Player(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	CircleRigidBody(m_circleShape, properties),
	m_circleShape(std::move(circleShape))
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

	switch (m_inputState)
	{
	case BUTTON_RIGHT:
		m_rbPosition.x += 5;
		m_circleShape.setScale(-1.f,1.f);
		break;

	case BUTTON_LEFT:
		m_rbPosition.x -= 5;
		m_circleShape.setScale(1.f, 1.f);
		break;

	case BUTTON_JUMP:
		// TODO:Make jump
		m_rbPosition.y -= 50.f;
		break;

	case BUTTON_LEFTCLICK:
		// TODO: Make shoot
		std::cout << "clicked" << std::endl;
		break;

	default:
		
		break;
	}
}