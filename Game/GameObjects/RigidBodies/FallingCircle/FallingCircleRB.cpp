#include "FallingCircleRB.h"

FallingCircleRB::FallingCircleRB()
	: FallingCircleRB({ 0.f, 0.f }, 0.f, sf::Color::White, { })
{ }

FallingCircleRB::FallingCircleRB(const sf::Vector2f& initialPos, float radius, const sf::Color& color, const PhysicsProperties& properties) :
	GameObject<PCFallingCircle, GCFallingCircle, ICVoid>(),
	CircleRigidBody(m_circleShape, properties)
{
	m_circleShape.setRadius(radius);
	m_circleShape.setOrigin(m_circleShape.getRadius(), m_circleShape.getRadius());

	m_circleShape.setFillColor(color);
	m_circleShape.setPosition(initialPos);

	m_rbPosition = m_circleShape.getPosition();
}