#pragma once

#include <array>

#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

#include "ExplosionFragments/ExplosionFragment.h"

constexpr int NUM_EXPLOSION_FRAGMENTS = 4;

class FragmentationBall : public Grenade
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~FragmentationBall() override = default;

	void setFragmentsForceMinMax(float minForce, float maxForce);

private:
	FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onBeginPlay(Engine::IScene& scene) override;

	void onCollisionEnter(IRigidBody* rb) override;

	float m_fragsMinForce;
	float m_fragsMaxForce;

	std::array<ExplosionFragment*, NUM_EXPLOSION_FRAGMENTS> m_childrenFragments;
};
