#include "PhysicsWorld.h"

#include "Engine/Utility/VectorUtils.h"
#include "Game/GameObjects/Player/Player.h"
#include "Game/Physics/RigidBodies/BoxRigidBody.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/RigidBodies/IRigidBody.h"
#include "Game/Physics/CollisionExternalDispatcher.h"

void PhysicsWorld::step(const float& deltaTime) const
{
	// -------- Update movements
	for (const auto& rb : m_rigidBodies)
	{
		rb->step(deltaTime);
	}

	// -------- Update collisions
	for (int a = 0; a < static_cast<int>(m_rigidBodies.size()) - 1; ++a)
	{
		const auto rbA = m_rigidBodies[a];

		if (!rbA->getPhysicsProperties().m_isActive)
			continue;

		for (int b = a + 1; b < static_cast<int>(m_rigidBodies.size()); ++b)
		{
			const auto rbB = m_rigidBodies[b];

			if (!rbB->getPhysicsProperties().m_isActive)
				continue;

			// ---- Static bodies check
			if (rbA->getPhysicsProperties().m_isStatic && rbB->getPhysicsProperties().m_isStatic)
				continue;

			CollisionUtils::HitResult hitResult;
			if (collide(rbA, rbB, hitResult))
			{
				rbA->tryOnCollisionEnter(rbB);
				rbB->tryOnCollisionEnter(rbA);

				// ---- Traversable bodies check
				if (rbA->getPhysicsProperties().m_isTraversable || rbB->getPhysicsProperties().m_isTraversable)
					continue;

				// ---- Move bodies apart
				// TODO : An object with m_canBounceOff = false will slide on surfaces, due to this calculation. If we don't the object falls due to gravity.
				const auto depthTranslation = hitResult.normal * hitResult.depth / 2.f;
				rbA->translate(depthTranslation);
				rbB->translate(-depthTranslation);

				// ---- Bounce off bodies check
				if (!rbA->getPhysicsProperties().m_canBounceOff && !rbB->getPhysicsProperties().m_canBounceOff)
					continue;

				const auto relativeVelocity = rbB->getVelocity() - rbA->getVelocity();

				// ---- Check if bodies are not already moving appart
				if (VectorUtils::Dot(relativeVelocity, hitResult.normal) < 0.f)
					continue;

				// ---- Bounce calculations and velocity changing
				const auto e = std::min(rbA->getPhysicsProperties().m_bounciness, rbB->getPhysicsProperties().m_bounciness);

				const auto j = -(1.f + e) * VectorUtils::Dot(relativeVelocity, hitResult.normal) /
					(rbA->getPhysicsProperties().m_invMass + rbB->getPhysicsProperties().m_invMass);

				const auto impulse = j * hitResult.normal;

				rbA->setVelocity(rbA->getPhysicsProperties().m_canBounceOff ?
					rbA->getVelocity() - impulse * rbA->getPhysicsProperties().m_invMass : VectorUtils::zero);

				rbB->setVelocity(rbB->getPhysicsProperties().m_canBounceOff ?
					rbB->getVelocity() + impulse * rbB->getPhysicsProperties().m_invMass : VectorUtils::zero);
			}
			else // If not collision
			{
				rbA->tryOnCollisionExit(rbB);
				rbB->tryOnCollisionExit(rbA);
			}
		}
	}
}

bool PhysicsWorld::collide(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& hitResult)
{
	// Todo : Use a double dynamic dispatcher to handle those if-statements.

	if (rbA->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
	{
		MakeCollision<CircleRigidBody>()(rbA, rbB, hitResult);
	}
	else if (rbA->getInstanceRTTI() == BoxRigidBody::getClassRTTI())
	{
		MakeCollision<BoxRigidBody>()(rbA, rbB, hitResult);
	}
	else if (rbA->getInstanceRTTI() == TerrainRigidBody::getClassRTTI())
	{
		MakeCollision<TerrainRigidBody>()(rbA, rbB, hitResult);
	}

	return hitResult.hasHit;
}

void PhysicsWorld::addRigidBody(IRigidBody& rb)
{
	m_rigidBodies.push_back(&rb);
}

void PhysicsWorld::removeRigidBody(IRigidBody& rb)
{
	m_rigidBodies.erase(std::ranges::find(m_rigidBodies, &rb));
}