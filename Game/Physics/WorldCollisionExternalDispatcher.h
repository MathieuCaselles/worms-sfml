#pragma once

#include <iostream>

#include "IRigidBody.h"
#include "RigidBodies/CircleRigidBody.h"
#include "RigidBodies/BoxRigidBody.h"
#include "RigidBodies/TerrainRigidBody.h"

template<typename... Tl>
struct TypeList {};

template<typename RigidBodyTypeA, typename RigidBodyTypeB>
struct CollisionHandler;

// --- Circle to...
template<>
struct CollisionHandler<CircleRigidBody, CircleRigidBody> { void operator()(CircleRigidBody*, CircleRigidBody*)   { std::cout << "Circle-Circle" << std::endl; } };

template<>
struct CollisionHandler<CircleRigidBody, BoxRigidBody> { void operator()(CircleRigidBody*, BoxRigidBody*)         { std::cout << "Circle-Box" << std::endl; } };

template<>
struct CollisionHandler<CircleRigidBody, TerrainRigidBody> { void operator()(CircleRigidBody*, TerrainRigidBody*) { std::cout << "Circle-Terrain" << std::endl; } };

// --- Box to...
template<>
struct CollisionHandler<BoxRigidBody, CircleRigidBody> { void operator()(BoxRigidBody*, CircleRigidBody*)         { std::cout << "Box-Circle" << std::endl; } };

template<>
struct CollisionHandler<BoxRigidBody, BoxRigidBody> { void operator()(BoxRigidBody*, BoxRigidBody*)               { std::cout << "Box-Box" << std::endl; } };

template<>
struct CollisionHandler<BoxRigidBody, TerrainRigidBody> { void operator()(BoxRigidBody*, TerrainRigidBody*)       { std::cout << "Box-Terrain" << std::endl; } };

// --- Terrain to...
template<>
struct CollisionHandler<TerrainRigidBody, TerrainRigidBody> { void operator()(TerrainRigidBody*, TerrainRigidBody*) { std::cout << "Terrain-Terrain" << std::endl; } };

template<template<typename RigidBodyTypeA, typename RigidBodyTypeB> class FnToDispatch, typename RigidBodyTypeList>
class WorldCollisionExternalDispatcher {};

template<template<typename RigidBodyTypeA, typename RigidBodyTypeB> class FnToDispatch, typename... AllRigidBodiesTypes>
class WorldCollisionExternalDispatcher<FnToDispatch, TypeList<AllRigidBodiesTypes...> >
{
public:
    template<typename RigidBodyTypeA, typename RigidBodyTypeB>
    void invokeIfRequired(IRigidBody* rbA, IRigidBody* rbB)
    {
        if (rbA->getInstanceRTTI() == RigidBodyTypeA::getClassRTTI() &&
            rbB->getInstanceRTTI() == RigidBodyTypeB::getClassRTTI())
        {
            FnToDispatch<RigidBodyTypeA, RigidBodyTypeB>()(static_cast<RigidBodyTypeA*>(rbA), static_cast<RigidBodyTypeB*>(rbB));
        }
    }

    void operator()(IRigidBody* rbA, IRigidBody* rbB)
    {
        (invokeIfRequired<AllRigidBodiesTypes, AllRigidBodiesTypes>(rbA, rbB), ...);
    }
};

using AllColisionnableRBs = TypeList<CircleRigidBody, BoxRigidBody, TerrainRigidBody>;

void testExternalDispatchRenderer(IRigidBody* rbA, IRigidBody* rbB)
{
    WorldCollisionExternalDispatcher<CollisionHandler, AllColisionnableRBs>()(rbA, rbB);
}