#include "FallingBox.h"

FallingBox::FallingBox()
	: FallingBox( sf::RectangleShape(), {})
{ }

FallingBox::FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties)
	: FallingBox(std::move(rectangleShape), properties, rectangleShape.getPosition(), rectangleShape.getRotation())
{ }

FallingBox::FallingBox(sf::RectangleShape rectangleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float initialRotation)
	: GameObject<PCFallingBox, GCFallingBox, ICVoid>(),
		BoxRigidBody(m_rectangleShape, properties),
		m_rectangleShape(std::move(rectangleShape))
{
	BoxRigidBody::updateMass();

	m_rbPosition = initialPosition;
	m_rbRotation = initialRotation;

	m_rectangleShape.setPosition(m_rbPosition);
	m_rectangleShape.setRotation(m_rbRotation);
}