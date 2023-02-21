#pragma once

#include "IRigidBody.h"
#include "Game/GameObjects/RigidBodies/Terrain/TerrainRB.h"
#include "RigidBodies/CircleRigidBody.h"
#include "RigidBodies/BoxRigidBody.h"
#include "RigidBodies/TerrainRigidBody.h"

template<typename... Tl>
struct TypeList {};

template<typename RigidBodyTypeA, typename RigidBodyTypeB>
struct CollisionHandler;

// --- Circle to...
template<>
struct CollisionHandler<CircleRigidBody, CircleRigidBody>
{
    void operator()(CircleRigidBody* rbA, CircleRigidBody* rbB, CollisionUtils::HitResult& outHitResult)
    {
		CollisionUtils::circleToCircle(
			rbA->getCircleShape().getPosition(), rbA->getCircleShape().getRadius(),
			rbB->getCircleShape().getPosition(), rbB->getCircleShape().getRadius(), 
			outHitResult);
    }
};

template<>
struct CollisionHandler<CircleRigidBody, BoxRigidBody>
{
	void operator()(CircleRigidBody* rbA, BoxRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::circleToPolygon(
			rbA->getCircleShape().getPosition(), rbA->getCircleShape().getRadius(),
			rbB->getRectPoints(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<CircleRigidBody, TerrainRigidBody>
{
	void operator()(CircleRigidBody* rbA, TerrainRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::circleAboveMultiLines(
			rbB->getTerrain().getFloorEdges(), 
			rbA->getCircleShape().getPosition(), rbA->getCircleShape().getRadius(),
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
			rbA->getRectPoints(),
			rbB->getCircleShape().getPosition(), rbB->getCircleShape().getRadius(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<BoxRigidBody, BoxRigidBody>
{
	void operator()(BoxRigidBody* rbA, BoxRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		CollisionUtils::polygonToPolygon(
			rbA->getRectPoints(),
			rbB->getRectPoints(),
			outHitResult);
	}
};

template<>
struct CollisionHandler<BoxRigidBody, TerrainRigidBody>
{
	void operator()(BoxRigidBody* rbA, TerrainRigidBody* rbB, CollisionUtils::HitResult& outHitResult) const
	{
		outHitResult.hasHit = false; // TODO : Handle Box - Terrain collision
	}
};

// --- Terrain to...
template<>
struct CollisionHandler<TerrainRigidBody, TerrainRigidBody>
{
	void operator()(TerrainRigidBody*, TerrainRigidBody*, CollisionUtils::HitResult& outHitResult) const
	{
		// Terrain - terrain collision not handled
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

using AllColisionnableRBs = TypeList<CircleRigidBody, BoxRigidBody, TerrainRigidBody>;

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