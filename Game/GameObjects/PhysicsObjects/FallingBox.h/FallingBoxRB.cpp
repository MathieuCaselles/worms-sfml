#include "FallingBoxRB.h"

FallingBoxRB::FallingBoxRB()
	: FallingBoxRB({ 0.f, 0.f }, { 0.f, 0.f }, sf::Color::White, { })
{ }

FallingBoxRB::FallingBoxRB(const sf::Vector2f& initialPos, const sf::Vector2f& size, const sf::Color& color, const PhysicsProperties& properties) :
	GameObject<PCFallingBox, GCFallingBox, ICVoid>(),
	BoxRigidBody(m_rectangleShape, properties)
{
	m_rectangleShape.setPosition(initialPos);
	m_rectangleShape.setSize(size);
	m_rectangleShape.setOrigin(size.x / 2.f, size.y / 2.f);
	m_rectangleShape.setFillColor(color);

	m_rbPosition = m_rectangleShape.getPosition();
}