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

	void setDurationExplosion(float duration) { m_durationExplosion = duration; }

	void onCollisionEnter(IRigidBody* rb) override;

	void tryToPlayExplosionFX();

	float getDamage();
	void setDamage(float damage);

	bool getCanPlayExplosionFX();

private:
	CircleExplosion();
	CircleExplosion(const sf::CircleShape& circleShape);

private:
	sf::CircleShape m_explosionCircleShape;

	float m_durationExplosion{ 0.1f };
	float m_currentTime{ 0.f };

	float m_damage;

	bool m_canPlayExplosionFX;

	sf::Texture m_explosionFX;

	sf::IntRect m_rectSourceSprite;

	sf::Sprite m_spriteExplosionFX;
	sf::Clock m_clockForExplosionFX;

};
