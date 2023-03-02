#pragma once

#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"

class ExplosionFragment : public Grenade
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;

public:
	~ExplosionFragment() override = default;

protected:
	ExplosionFragment(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onBeginPlay(Engine::IScene& scene) override;
	void onCollisionEnter(IRigidBody* rb) override;
};
