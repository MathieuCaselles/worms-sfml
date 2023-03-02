#pragma once

#include <array>

#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

constexpr int NUM_EXPLOSION_FRAGMENTS = 5;

class ExplosionFragment;

class FragmentationBall : public Grenade
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~FragmentationBall() override = default;

	void setFragmentsForceMinMax(float minForce, float maxForce);
	void setFragmentsDamage(float dmg) { m_fragmentsDamage = dmg; }
	void setFragmentsDurationBeforeExplosion(float dmg) { m_fragmentsDurationBeforeExplosion = dmg; }

private:
	FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties);
	void updateImplementation(const float& deltaTime, IGameObject& gameObject, Engine::IScene& scene) override;
	void renderImplementation(IGameObject& gameObject, sf::RenderWindow& window) override;

	void onBeginPlay(Engine::IScene& scene) override;

	void onCollisionEnter(IRigidBody* rb) override { };
	void startExplosion() override;

	float m_fragsMinForce { 0.f };
	float m_fragsMaxForce { 0.f };

	float m_fragmentsDamage{ 0.f };
	float m_fragmentsDurationBeforeExplosion{ 0.f };

	std::array<ExplosionFragment*, NUM_EXPLOSION_FRAGMENTS> m_childrenFragments;
};
