#pragma once

#include "Engine/GameObject/GameObject.h"

#include "Game/Components/GraphicsComponents/GCVoid.h"
#include "PCPhysicsWorld.h"
#include "Game/Components/InputComponents/ICVoid.h"

class IRigidBody;

class PhysicsWorld : public Engine::GameObject<PCPhysicsWorld, GCVoid, ICVoid>
{
	friend PCPhysicsWorld;

public:
	inline static const sf::Vector2f GRAVITY_FORCE{ 0, 9.81f };

public:
	void addRigidBody(IRigidBody& rb);
	void removeRigidBody(IRigidBody& rb);

	[[nodiscard]] const std::vector<IRigidBody*>& getAllRigidBodies() const { return m_rigidBodies; }

private:
	std::vector<IRigidBody*> m_rigidBodies;
};
