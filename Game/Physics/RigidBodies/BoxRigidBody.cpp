#include "BoxRigidBody.h"

#include "Game/Physics/PhysicsWorld.h"

BoxRigidBody::BoxRigidBody(const sf::RectangleShape& rectangleShape, const PhysicsProperties& properties)
	: IRigidBody(properties),
	m_rectangleCollisionShape(rectangleShape)
{
	m_rectangleCollisionShape.setFillColor(sf::Color(0, 0, 0, 0));
	m_rectangleCollisionShape.setOutlineColor(sf::Color(0, 0, 0, 0));

	m_rectangleCollisionShape.setOrigin(m_rectangleCollisionShape.getSize().x / 2, m_rectangleCollisionShape.getSize().y / 2);
}

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
