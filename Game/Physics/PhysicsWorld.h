#pragma once

#include "Engine/GameObject/GameObject.h"

#include "Game/Components/GraphicsComponents/GCVoid.h"
#include "Game/Physics/PCPhysicsWorld.h"
#include "Game/Components/InputComponents/ICVoid.h"

class IRigidBody;

class PhysicsWorld : public Engine::GameObject<PCPhysicsWorld, GCVoid, ICVoid>
{
	friend PCPhysicsWorld;

public:
	// World objects density table : https://www.thoughtco.com/table-of-densities-of-common-substances-603976
	inline static constexpr float MIN_DENSITY = 0.534f; // Lithium density
	inline static constexpr float MAX_DENSITY = 22.6f; // Iridium density

	inline static const sf::Vector2f GRAVITY{ 0, 9.81f };

public:
	PhysicsWorld() = default;

	void onBeginPlay(Engine::IScene& scene) override;

	void addRigidBody(IRigidBody& rb);
	void removeRigidBody(IRigidBody& rb);

	IRigidBody* getRigidBody(IRigidBody& rb);

private:
	std::vector<IRigidBody*> m_rigidBodies;

};
