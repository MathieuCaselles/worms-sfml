#include "PCForceVolume.h"

#include "ForceVolume.h"
#include "Game/Physics/RigidBodies/IRigidBody.h"

void PCForceVolume::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	const auto& forceVolume = reinterpret_cast<ForceVolume&>(gameObject);

	for (const auto& rb : forceVolume.m_rigidBodies)
	{
		rb->addForce(forceVolume.m_force);
	}
}
