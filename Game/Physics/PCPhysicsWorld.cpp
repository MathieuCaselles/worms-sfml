#include "PCPhysicsWorld.h"

#include <iostream>

#include "IRigidBody.h"
#include "PhysicsWorld.h"
#include "Engine/Utility/CollisionUtils.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "RigidBodies/BoxRigidBody.h"

PCPhysicsWorld::PCPhysicsWorld()
{ }

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
	if (rbA->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
	{
		const auto currentCircleRB = reinterpret_cast<CircleRigidBody*>(rbA);

		if (rbB->getInstanceRTTI() == CircleRigidBody::getClassRTTI()) // Circle to circle
		{
			const auto otherCircleRb = reinterpret_cast<CircleRigidBody*>(rbB);
			return CollisionUtils::circleToCircle(
			currentCircleRB->getCircleShape().getPosition(), currentCircleRB->getCircleShape().getRadius(),
			otherCircleRb->getCircleShape().getPosition(), otherCircleRb->getCircleShape().getRadius(), 
				hitResult);
		}
		
		if (rbB->getInstanceRTTI() == BoxRigidBody::getClassRTTI()) // Circle to box
		{
			const auto otherBoxRb = reinterpret_cast<BoxRigidBody*>(rbB);
			return CollisionUtils::circleToPolygon(
				currentCircleRB->getCircleShape().getPosition(), currentCircleRB->getCircleShape().getRadius(),
				otherBoxRb->getRectPoints(), 
				hitResult);
		}
	}
	else if (rbA->getInstanceRTTI() == BoxRigidBody::getClassRTTI()) // Box to circle
	{
		const auto currentBoxRB = reinterpret_cast<BoxRigidBody*>(rbA);

		if (rbB->getInstanceRTTI() == CircleRigidBody::getClassRTTI())
		{
			const auto otherCircleRb = reinterpret_cast<CircleRigidBody*>(rbB);
			return CollisionUtils::polygonToCircle(
				currentBoxRB->getRectPoints(), 
				otherCircleRb->getCircleShape().getPosition(), otherCircleRb->getCircleShape().getRadius(), 
				hitResult);
		}
		
		if (rbB->getInstanceRTTI() == BoxRigidBody::getClassRTTI()) // Box to box
		{
			const auto otherBoxRb = reinterpret_cast<BoxRigidBody*>(rbB);
			return CollisionUtils::polygonToPolygon(
				currentBoxRB->getRectPoints(), 
				otherBoxRb->getRectPoints(), 
				hitResult);
		}
	}

	return false;
}
