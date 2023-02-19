#include "PCPhysicsWorld.h"

#include <iostream>

#include "IRigidBody.h"
#include "PhysicsWorld.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"

PCPhysicsWorld::PCPhysicsWorld()
{ }

void PCPhysicsWorld::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& world = reinterpret_cast<PhysicsWorld&>(gameObject);

	// -------- Update movements
	for (const auto& rb : world.m_rigidBodies)
	{
		rb->setVelocity(PhysicsWorld::GRAVITY);
		rb->step(deltaTime);
	}

	// -------- Update collisions
	for (const auto& currentRb : world.m_rigidBodies)
	{
		if (currentRb->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
		{
			std::cout << "Updating collision of rb";
		}
	}
}