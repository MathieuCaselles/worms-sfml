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

std::vector<sf::Vector2f> BoxRigidBody::getRectPoints() const
{
	std::vector<sf::Vector2f> vectorResult;

	vectorResult.reserve(m_rectangleShape.getPointCount());
	for (int i = 0; i < static_cast<int>(m_rectangleShape.getPointCount()); ++i)
	{
		vectorResult.emplace_back(m_rectangleShape.getTransform().transformPoint(m_rectangleShape.getPoint(i)));
	}

	return vectorResult;
}
