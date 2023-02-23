#pragma once

#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"

#include "Game/Physics/RigidBodies/IRigidBody.h"
#include "RigidBodies/CircleRigidBody.h"
#include "RigidBodies/BoxRigidBody.h"
#include "RigidBodies/TerrainRigidBody.h"

/**
 * External dispatcher pattern, deriving from the insane RTTI.
 *
 * WorldCollisionExternalDispatcher will check the two Rigid-Bodies type and will call the right
 * CollisionHandler to solve the collision, depending of the two Rigid-Bodies type.
 *
 * To use all of this system, you can call MakeCollision<RigidBodyType>.
 * For now, collision working from CircleRigidBody/BoxRigidBodies to CircleRigidBody/BoxRigidBodies/TerrainRigidBody.
 */

template<typename... Tl>
struct TypeList {};

using AllColisionnableRBs = TypeList<CircleRigidBody, BoxRigidBody, TerrainRigidBody>;

template<typename RigidBodyTypeA, typename RigidBodyTypeB>
struct CollisionHandler;

// --- Circle to...
template<>
struct CollisionHandler<CircleRigidBody, CircleRigidBody>
{
    void operator()(CircleRigidBody* rbA, CircleRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
    {
		CollisionUtils::circleToCircle(
			rbA->getPosition(), rbA->getRadius(),
			rbB->getPosition(), rbB->getRadius(), 
			outHitResult);
    }
};

template<>
struct CollisionHandler<CircleRigidBody, BoxRigidBody>
{
	void operator()(CircleRigidBody* rbA, BoxRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::circleToPolygon(
			rbA->getPosition(), rbA->getRadius(),
			rbB->getTransformRectPoints(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<CircleRigidBody, TerrainRigidBody>
{
	void operator()(CircleRigidBody* rbA, TerrainRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::circleAboveMultiLines(
			rbB->getEdges(),
			rbA->getPosition(), rbA->getRadius(),
			outHitResult);
	}
};

// --- Box to...
template<>
struct CollisionHandler<BoxRigidBody, CircleRigidBody>
{
	void operator()(BoxRigidBody* rbA, CircleRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::polygonToCircle(
			rbA->getTransformRectPoints(),
			rbB->getPosition(), rbB->getRadius(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<BoxRigidBody, BoxRigidBody>
{
	void operator()(BoxRigidBody* rbA, BoxRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::polygonToPolygon(
			rbA->getTransformRectPoints(),
			rbB->getTransformRectPoints(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<BoxRigidBody, TerrainRigidBody>
{
	void operator()(BoxRigidBody* rbA, TerrainRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::polygonAboveMultilines(
			rbB->getEdges(),
			rbA->getTransformRectPoints(),
			outHitResult);
	}
};

template<template<typename RigidBodyTypeA, typename RigidBodyTypeB> class FnToDispatch, typename LeftRB, typename RigidBodyTypeList>
class WorldCollisionExternalDispatcher {};

template<template<typename RigidBodyTypeA, typename RigidBodyTypeB> class FnToDispatch, typename LeftRB, typename... AllRigidBodiesTypes>
class WorldCollisionExternalDispatcher<FnToDispatch, LeftRB, TypeList<AllRigidBodiesTypes...>>
{
public:
    template<typename RigidBodyTypeA, typename RigidBodyTypeB>
    void invokeIfRequired(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
    {
        if (rbA->getInstanceRTTI() == RigidBodyTypeA::getClassRTTI() &&
            rbB->getInstanceRTTI() == RigidBodyTypeB::getClassRTTI())
        {
            FnToDispatch<RigidBodyTypeA, RigidBodyTypeB>()(static_cast<RigidBodyTypeA*>(rbA), static_cast<RigidBodyTypeB*>(rbB), outHitResult);
        }
    }

    void operator()(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
    {
        (invokeIfRequired<LeftRB, AllRigidBodiesTypes>(rbA, rbB, outHitResult), ...);
    }
};

template<typename RigidBodyType>
struct MakeCollision
{
	void operator()(IRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& outHitResult) { }
};

template<>
struct MakeCollision<CircleRigidBody>
{
	void operator()(CircleRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
	{
		WorldCollisionExternalDispatcher<CollisionHandler, CircleRigidBody, AllColisionnableRBs>()(rbA, rbB, outHitResult);
	}
};

template<>
struct MakeCollision<BoxRigidBody>
{
	void operator()(BoxRigidBody* rbA, IRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
	{
		WorldCollisionExternalDispatcher<CollisionHandler, BoxRigidBody, AllColisionnableRBs>()(rbA, rbB, outHitResult);
	}
};