#pragma once

#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"
#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class ExplosionFragment;

class FragmentationBall : public Grenade
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~FragmentationBall() override = default;

	void setFragmentsForceMinMax(float minForce, float maxForce);
	void setFragmentsDamage(float dmg) { m_fragsDamage = dmg; }
	void setFragmentsDurationBeforeExplosion(float dmg) { m_fragsDurationBeforeExplosion = dmg; }
	void setFragsSpawnXAngleIncertitude(int incertitude) { m_fragsSpawnXAngleIncertitude = incertitude; }

private:
	FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties, int numFragments);
	void updateImplementation(const float& deltaTime, IGameObject& gameObject, Engine::IScene& scene) override;
	void renderImplementation(IGameObject& gameObject, sf::RenderWindow& window) override;

	void onBeginPlay(Engine::IScene& scene) override;

	void onCollisionEnter(IRigidBody* rb) override;

	void startExplosion() override;

	float m_fragsMinForce { 0.f };
	float m_fragsMaxForce { 0.f };

	int m_fragsSpawnXAngleIncertitude{ 40 };
	float m_fragsDamage{ 0.f };
	float m_fragsDurationBeforeExplosion{ 0.f };

	int m_numFragments;

	std::vector<ExplosionFragment*> m_childrenFragments;
};
