#pragma once

#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"

class ExplosionFragment : public Grenade
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;

public:
	~ExplosionFragment() override = default;
	void shot(const sf::Vector2f& position, const sf::Vector2f& direction) override;
	void startExplosion() override;

	void onCollisionEnter(IRigidBody* rb) override;
	void updateImplementation(const float& deltaTime, IGameObject& gameObject, Engine::IScene& scene) override;
	void renderImplementation(IGameObject& gameObject, sf::RenderWindow& window) override;

protected:
	ExplosionFragment(sf::CircleShape circleShape, const PhysicsProperties& properties);

	void onBeginPlay(Engine::IScene& scene) override;
};
