#pragma once

#include "GCGrenade.h"
#include "PCGrenade.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/CircleExplosion/CircleExplosion.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class MainGameScene;

class Grenade : public Engine::GameObject<PCGrenade, GCGrenade, ICVoid>,
                public CircleRigidBody
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~Grenade() override = default;

	/** Use this method to shot the grenade */
	void shot(const sf::Vector2f& position, const sf::Vector2f& direction);

	void setLaunchForce(float force) { m_launchForce = force; }
	float getLaunchForce() const { return m_launchForce; }

private:
	Grenade(const Grenade& grenade) = default;
	Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onBeginPlay(Engine::IScene& scene) override;

	void onCollisionEnter(IRigidBody* rb) override;

	void updateGrenadeActivation(bool showGrenade, bool showExplosion);

private:
	CircleExplosion* m_circleExplosion;

	sf::CircleShape m_circleShape;
	float m_launchForce{ 10.f };
};
