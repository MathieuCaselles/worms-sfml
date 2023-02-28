#include "BoxRigidBody.h"

#include "Game/Physics/PhysicsWorld.h"

BoxRigidBody::BoxRigidBody(sf::RectangleShape& rectangleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	m_rectangleCollisionShape(rectangleShape)
{ }

void BoxRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);

	m_rectangleCollisionShape.setPosition(m_rbPosition);
	m_rectangleCollisionShape.setRotation(m_rbRotation);
}

void BoxRigidBody::updateMass()
{
	const float surfaceArea = m_rectangleCollisionShape.getSize().x * m_rectangleCollisionShape.getSize().y * PHYSICS_UNIT_METER_PER_PIXEL;
	m_rbProperties.m_mass = surfaceArea * m_rbProperties.m_density;

	IRigidBody::updateMass();
}

std::vector<sf::Vector2f> BoxRigidBody::getTransformRectPoints() const
{
	std::vector<sf::Vector2f> vectorResult;

	vectorResult.reserve(m_rectangleCollisionShape.getPointCount());
	for (int i = 0; i < static_cast<int>(m_rectangleCollisionShape.getPointCount()); ++i)
	{
		vectorResult.emplace_back(m_rectangleCollisionShape.getTransform().transformPoint(m_rectangleCollisionShape.getPoint(i)));
	}

	return vectorResult;
}
