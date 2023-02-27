#include "BlackHole.h"

#include <utility>

#include "Game/Components/PhysicsComponents/PCVoid.h"
#include "Game/Physics/PhysicsProperties.h"

BlackHole::BlackHole()
	: BlackHole(sf::CircleShape(), {}, {})
{ }

BlackHole::BlackHole(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition)
	: GameObject<PCBlackHole, GCBlackHole, ICVoid>(),
	CircleRigidBody(m_blackHoleShape, properties),
	m_blackHoleShape(std::move(circleShape))
{
	CircleRigidBody::updateMass();

	m_rbPosition = initialPosition;

	m_blackHoleShape.setPosition(m_rbPosition);
	m_blackHoleShape.setRotation(m_rbRotation);
}