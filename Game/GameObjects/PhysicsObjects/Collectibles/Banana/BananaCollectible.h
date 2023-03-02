#pragma once

#include "GCBananaCollectible.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Components/PhysicsComponents/PCVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"

class BananaCollectible : public Engine::GameObject<PCVoid, GCBananaCollectible, ICVoid>,
	public CircleRigidBody
{
	friend class Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
	friend GCBananaCollectible;

public:
	~BananaCollectible() override = default;

	void onCollisionEnter(IRigidBody* rb) override;

	void show(sf::Vector2f spawnPoint);
	void hide();

	std::function<void()> m_onCollectCallback;

private:
	explicit BananaCollectible(const sf::CircleShape& circleShape);

private:
	sf::CircleShape m_bananaShape;

};
