#include "CircleExplosion.h"

#include "Engine/GameObject/GameObject.h"

CircleExplosion::CircleExplosion()
	: Engine::GameObject<PCCircleExplosion, GCCircleExplosion, ICVoid>(), CircleRigidBody(sf::CircleShape(), {})
{ }

CircleExplosion::CircleExplosion(const sf::CircleShape& circleShape)
	: Engine::GameObject<PCCircleExplosion, GCCircleExplosion, ICVoid>(), CircleRigidBody(circleShape, {}),
	m_explosionCircleShape(circleShape)
{
	CircleRigidBody::updateMass();

	m_rbProperties.m_isStatic = true;
	m_rbProperties.m_isTraversable = true;
	m_rbProperties.m_isActive = false;

	m_explosionCircleShape.setPosition(m_rbPosition);

	setIsActive(false);
}

void CircleExplosion::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);

	setIsActive(false);
}
