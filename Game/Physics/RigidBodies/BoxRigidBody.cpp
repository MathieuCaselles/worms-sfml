#include "BoxRigidBody.h"

BoxRigidBody::BoxRigidBody(sf::RectangleShape& rectangleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	m_rectangleShape(rectangleShape)
{
	if (m_rbProperties.m_mass < 0.0001f)
	{
		const float surfaceArea = m_rectangleShape.getSize().x * m_rectangleShape.getSize().y;
		m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;
	}
}

void BoxRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);
}
