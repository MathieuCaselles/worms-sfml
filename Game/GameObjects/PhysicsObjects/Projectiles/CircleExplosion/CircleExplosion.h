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

	sf::CircleShape& getExplosionCircleShape() { return m_explosionCircleShape; }

private:
	CircleExplosion();
	CircleExplosion(const sf::CircleShape& circleShape);

private:
	sf::CircleShape m_explosionCircleShape;
};
