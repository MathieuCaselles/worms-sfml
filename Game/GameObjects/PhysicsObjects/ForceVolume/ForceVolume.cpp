#include "ForceVolume.h"

#include "Game/Physics/RigidBodies/IRigidBody.h"

ForceVolume::ForceVolume(const std::vector<IRigidBody*> rigidBodies, const sf::Vector2f& force)
	: m_rigidBodies(rigidBodies), m_force(force)
{
}

void ForceVolume::addRigidBody(IRigidBody& rb)
{
	m_rigidBodies.push_back(&rb);
}

void ForceVolume::removeRigidBody(IRigidBody& rb)
{
	m_rigidBodies.erase(std::ranges::find(m_rigidBodies, &rb));
}