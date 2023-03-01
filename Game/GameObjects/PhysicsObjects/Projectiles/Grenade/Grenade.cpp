#include "Grenade.h"

#include "Engine/GameObject/GameObject.h"

Grenade::Grenade()
	: Grenade(sf::CircleShape(), {})
{ }

Grenade::Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Engine::GameObject<PCGrenade, GCGrenade, ICVoid>(),
	  CircleRigidBody(circleShape, properties),
	  m_circleShape(std::move(circleShape))
{
	CircleRigidBody::updateMass();

	m_circleShape.setPosition(m_rbPosition);

	setIsActive(false);
}

void Grenade::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);

	setIsActive(false);
}
