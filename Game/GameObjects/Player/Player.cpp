#include "Player.h"

#include <iostream>

Player::Player()
	: Player(sf::RectangleShape(), {})
{ }

Player::Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties)
	: Player(std::move(rectangleShape), properties, rectangleShape.getPosition(), rectangleShape.getRotation())
{ }

Player::Player(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCPlayer, GCPlayer, ICPlayer>(),
	BoxRigidBody(m_rectangleShape, properties),
	m_rectangleShape(std::move(rectangleShape))
{
	BoxRigidBody::updateMass();

	m_rbPosition = initialPosition;
	m_rbRotation = initialRotation;

	m_rectangleShape.setPosition(m_rbPosition);
	m_rectangleShape.setRotation(m_rbRotation);
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
		m_rectangleShape.setPosition(m_rectangleShape.getPosition().x + 100.f, m_rectangleShape.getPosition().y);
		break;

	case BUTTON_LEFT:
		m_rectangleShape.setPosition(m_rectangleShape.getPosition().x - 100.f, m_rectangleShape.getPosition().y);
		break;

	case BUTTON_JUMP:
		m_rectangleShape.setPosition(m_rectangleShape.getPosition().x, m_rectangleShape.getPosition().y - 100.f);
		std::cout << "x:" << m_rectangleShape.getPosition().x << " y:" << m_rectangleShape.getPosition().y << std::endl;
		break;

	case BUTTON_LEFTCLICK:
		m_rectangleShape.setPosition(m_rectangleShape.getPosition());
		std::cout << "clicked" << std::endl;
		break;

	default:
		
		break;
	}
}