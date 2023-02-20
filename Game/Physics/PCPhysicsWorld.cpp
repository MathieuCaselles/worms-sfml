#include "PCPhysicsWorld.h"

#include "IRigidBody.h"
#include "PhysicsWorld.h"
#include "Engine/Utility/CollisionUtils.h"

#include "WorldCollisionExternalDispatcher.h"

void PCPhysicsWorld::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& world = reinterpret_cast<PhysicsWorld&>(gameObject);

	// -------- Update movements
	for (const auto& rb : world.m_rigidBodies)
	{
		if(!rb->getProperties().m_isStatic)
		{
			rb->step(deltaTime);
		}
	}

	// -------- Update collisions
	for (int i = 0; i < static_cast<int>(world.m_rigidBodies.size()) - 1; ++i)
	{
		const auto currentRb = world.m_rigidBodies[i];

		for (int j = i + 1; j < static_cast<int>(world.m_rigidBodies.size()); ++j)
		{
			const auto otherRb = world.m_rigidBodies[j];

			CollisionUtils::HitResult hitResult;
			if (collide(currentRb, otherRb, hitResult))
			{
				currentRb->addForce(hitResult.normal * hitResult.depth / 2.f);
				otherRb->addForce(-hitResult.normal * hitResult.depth / 2.f);
			}
		}
	}
}

bool PCPhysicsWorld::collide(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& hitResult)
{
	tryWorldCollisionExternalDispatcher(rbA, rbB, hitResult);

	return hitResult.hasHit;
}
