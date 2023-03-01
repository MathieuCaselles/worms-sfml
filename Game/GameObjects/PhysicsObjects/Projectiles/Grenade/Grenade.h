#pragma once

#include "GCGrenade.h"
#include "PCGrenade.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class Grenade : public Engine::GameObject<PCGrenade, GCGrenade, ICVoid>,
				public CircleRigidBody
{
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;
	friend PCGrenade;

public:
	~Grenade() override = default;

	void setLaunchForce(float force) { m_launchForce = force; }
	float getLaunchForce() const { return m_launchForce; }

private:
	Grenade();
	Grenade(const Grenade& grenade) = default;
	Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onCollisionEnter(IRigidBody* rb) override;

private:
	sf::CircleShape m_circleShape;
	float m_launchForce{ 10.f };
};
