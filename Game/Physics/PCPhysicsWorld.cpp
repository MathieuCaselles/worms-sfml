#include "PCPhysicsWorld.h"

#include "IRigidBody.h"
#include "PhysicsWorld.h"

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

}