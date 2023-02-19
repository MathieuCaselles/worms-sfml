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
		for (const auto& otherRb : world.m_rigidBodies)
		{
			if (currentRb == otherRb)
				continue;

			if (currentRb->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
			{
				auto circleRB = reinterpret_cast<CircleRigidBody*>(currentRb);

				if(otherRb->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
				{
				}
			}
		}
	}
}