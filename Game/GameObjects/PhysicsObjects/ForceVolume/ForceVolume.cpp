#include "ForceVolume.h"

#include "Game/Physics/RigidBodies/IRigidBody.h"

ForceVolume::ForceVolume(const std::vector<IRigidBody*>& rigidBodies)
{
	for (const auto& rb : rigidBodies)
	{
		addRigidBody(*rb);
	}
}

void ForceVolume::addRigidBody(IRigidBody& rb)
{
	m_rigidBodies.push_back(&rb);
}

void ForceVolume::removeRigidBody(IRigidBody& rb)
{
	m_rigidBodies.erase(std::ranges::find(m_rigidBodies, &rb));
}