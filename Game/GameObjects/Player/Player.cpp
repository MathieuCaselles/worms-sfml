#include "Player.h"

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