#include "FallingBoxRB.h"

FallingBoxRB::FallingBoxRB()
	: FallingBoxRB( sf::RectangleShape(), {})
{ }

FallingBoxRB::FallingBoxRB(sf::RectangleShape rectangleShape, const PhysicsProperties& properties)
	: FallingBoxRB(std::move(rectangleShape), properties, rectangleShape.getPosition(), rectangleShape.getRotation())
{ }

FallingBoxRB::FallingBoxRB(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCFallingBox, GCFallingBox, ICVoid>(),
		BoxRigidBody(m_rectangleShape, properties),
		m_rectangleShape(std::move(rectangleShape))
{
	m_rbPosition = initialPosition;
	m_rbRotation = initialRotation;

	m_rectangleShape.setPosition(m_rbPosition);
	m_rectangleShape.setRotation(m_rbRotation);
}
