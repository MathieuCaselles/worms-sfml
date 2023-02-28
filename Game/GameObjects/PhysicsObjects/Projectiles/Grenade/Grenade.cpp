#include "Grenade.h"

#include <utility>

#include "Engine/GameObject/GameObject.h"

Grenade::Grenade()
	: Grenade(sf::CircleShape(), {}, {}, {})
{ }

Grenade::Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, const sf::Vector2f& initialVelocity)
	: Engine::GameObject<PCVoid, GCGrenade, ICVoid>(),
	  CircleRigidBody(m_circleShape, properties),
	  m_circleShape(std::move(circleShape))
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_circleShape.setPosition(m_rbPosition);

	m_rbVelocity = initialVelocity;
}

void Grenade::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);

	//Grenade::~Grenade();
}
