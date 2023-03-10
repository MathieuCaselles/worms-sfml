#pragma once

#include "GCGrenade.h"
#include "PCGrenade.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/CircleExplosion/CircleExplosion.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"


class Grenade : public Engine::GameObject<PCGrenade, GCGrenade, ICVoid>,
                public CircleRigidBody
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~Grenade() override = default;

	/** Use this method to shot the grenade */
	virtual void shot(const sf::Vector2f& position, const sf::Vector2f& direction);

	void setLaunchForce(float force) { m_launchForce = force; }
	float getLaunchForce() const { return m_launchForce; }
	
	void setDurationBeforeExplosion(float duration) { m_durationBeforeExplosion = duration; }

	bool hasExploded() const;

	std::function<void()> m_onExplosionCallback;

	void setDamages(float dmg) { m_damages = dmg; }
	float getDamages() const { return m_damages; }

protected:
	Grenade(const Grenade& grenade) = default;
	Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onBeginPlay(Engine::IScene& scene) override;
	void onCollisionEnter(IRigidBody* rb) override;

	virtual void startExplosion();

	void stopExplosion();
	void updateGrenadeActivation(bool showGrenade, bool showExplosion);

protected:
	CircleExplosion* m_circleExplosion;

	sf::CircleShape m_grenadeShape;
	sf::Texture m_grenadeTexture;

	float m_damages{ 0.f };

	/** Velocity when it spawn */
	float m_launchForce{ 10.f };

	/** Duration before forcing explosing (useful when it goes off the map) */
	float m_durationBeforeExplosion{ 4.f };
	float m_currentTime{ 0.f };

};
