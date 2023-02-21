#include "PCPhysicsWorld.h"

#include "Engine/Utility/CollisionUtils.h"
#include "Game/Physics/WorldCollisionExternalDispatcher.h"

#include "Game/Physics/RigidBodies/IRigidBody.h"
#include "PhysicsWorld.h"
#include "Engine/Utility/VectorUtils.h"

void PCPhysicsWorld::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& world = reinterpret_cast<PhysicsWorld&>(gameObject);

	// -------- Update movements
	for (const auto& rb : world.m_rigidBodies)
	{
		rb->step(deltaTime);
	}

	// -------- Update collisions
	for (int a = 0; a < static_cast<int>(world.m_rigidBodies.size()) - 1; ++a)
	{
		const auto rbA = world.m_rigidBodies[a];

		for (int b = a + 1; b < static_cast<int>(world.m_rigidBodies.size()); ++b)
		{
			const auto rbB = world.m_rigidBodies[b];

			CollisionUtils::HitResult hitResult;
			if (collide(rbA, rbB, hitResult))
			{
				// Move bodies apart
				rbA->translate(hitResult.normal * hitResult.depth / 2.f);
				rbB->translate(-hitResult.normal * hitResult.depth / 2.f);

				// Change velocity due to the collision
				sf::Vector2f relativeVelocity = rbB->getVelocity() - rbA->getVelocity();

				const auto e = std::min(rbA->getProperties().m_bounciness, rbB->getProperties().m_bounciness);

				const auto j = -(1.f + e) * VectorUtils::Dot(relativeVelocity, hitResult.normal) /
							  (1.f / rbA->getProperties().m_mass) + (1.f / rbB->getProperties().m_mass);

				rbA->setVelocity(rbA->getVelocity() - (j / rbA->getProperties().m_mass * hitResult.normal));
				rbB->setVelocity(rbB->getVelocity() + (j / rbB->getProperties().m_mass * hitResult.normal));
			}
		}
	}
}

bool PCPhysicsWorld::collide(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& hitResult)
{
	if(rbA->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
	{
		MakeCollision<CircleRigidBody>()(reinterpret_cast<CircleRigidBody*>(rbA), rbB, hitResult);
	}
	else if(rbA->getInstanceRTTI() == BoxRigidBody::getClassRTTI())
	{
		MakeCollision<BoxRigidBody>()(reinterpret_cast<BoxRigidBody*>(rbA), rbB, hitResult);
	}


	return hitResult.hasHit;
}
