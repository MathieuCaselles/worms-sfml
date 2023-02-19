#include "PhysicsWorld.h"

#include "IRigidBody.h"

void PhysicsWorld::onBeginPlay(Engine::IScene& scene)
{
	GameObject<PCPhysicsWorld, GCVoid, ICVoid>::onBeginPlay(scene);
}

void PhysicsWorld::addRigidBody(IRigidBody& rb)
{
	m_rigidBodies.push_back(&rb);
}

void PhysicsWorld::removeRigidBody(IRigidBody& rb)
{
	m_rigidBodies.remove(&rb);
}

IRigidBody* PhysicsWorld::getRigidBody(IRigidBody&& rb)
{
	return *std::ranges::find(m_rigidBodies, &rb);
}
