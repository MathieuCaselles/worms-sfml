#include "BoxRigidBody.h"

#include "Game/Physics/PhysicsWorld.h"

BoxRigidBody::BoxRigidBody(sf::RectangleShape& rectangleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	m_rectangleShape(rectangleShape)
{ }

void BoxRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);

	m_rectangleShape.setPosition(m_rbPosition);
}

void BoxRigidBody::updateMass()
{
	const float surfaceArea = m_rectangleShape.getSize().x * m_rectangleShape.getSize().y * PHYSICS_UNIT_METER_PER_PIXEL;
	m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;

	IRigidBody::updateMass();
}

std::vector<sf::Vector2f> BoxRigidBody::getTransformRectPoints() const
{
	std::vector<sf::Vector2f> vectorResult;

	vectorResult.reserve(m_rectangleShape.getPointCount());
	for (int i = 0; i < static_cast<int>(m_rectangleShape.getPointCount()); ++i)
	{
		vectorResult.emplace_back(m_rectangleShape.getTransform().transformPoint(m_rectangleShape.getPoint(i)));
	}

	return vectorResult;
}
