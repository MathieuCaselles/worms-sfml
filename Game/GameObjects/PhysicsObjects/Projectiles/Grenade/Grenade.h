#pragma once

#include "GCGrenade.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Components/PhysicsComponents/PCVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"
#include "Game/Physics/PhysicsProperties.h"

class Grenade : public Engine::GameObject<PCVoid, GCGrenade, ICVoid>,
				public CircleRigidBody
{
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCGrenade;

private:
	Grenade();
	Grenade(const Grenade& grenade) = default;
	Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition = {}, const sf::Vector2f& initialVelocity = {});

	void onCollisionEnter(IRigidBody* rb) override;

public:
	~Grenade() override = default;

	[[nodiscard]] const sf::CircleShape& getCircleShape() const { return m_circleShape; }

private:
	sf::CircleShape m_circleShape;
};
