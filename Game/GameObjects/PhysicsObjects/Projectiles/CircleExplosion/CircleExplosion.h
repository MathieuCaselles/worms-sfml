#pragma once

#include "GCCircleExplosion.h"
#include "PCCircleExplosion.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"

class CircleExplosion : public Engine::GameObject<PCCircleExplosion, GCCircleExplosion, ICVoid>,
						public CircleRigidBody
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend PCCircleExplosion;
	friend GCCircleExplosion;

public:
	~CircleExplosion() override = default;

private:
	CircleExplosion();
	CircleExplosion(const sf::CircleShape& circleShape);

	void onCollisionEnter(IRigidBody* rb) override;

private:
	sf::CircleShape m_explosionCircleShape;
};
