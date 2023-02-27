#pragma once

#include "PCBlackHole.h"
#include "GCBlackHole.h"
#include "Game/Components/InputComponents/ICVoid.h"

#include "Game/Physics/RigidBodies/CircleRigidBody.h"

class BlackHole : public Engine::GameObject<PCBlackHole, GCBlackHole, ICVoid>,
                  public CircleRigidBody
{
	friend GCBlackHole;
	friend PCBlackHole;


public:
	BlackHole();
	BlackHole(sf::CircleShape circleShape, const PhysicsProperties& properties, const sf::Vector2f& initialPosition, float centerAttractionForce);

	~BlackHole() override = default;

	void setCenterAttractionForce(float force);
	float getCenterAttractionForce() const;

	[[nodiscard]] const sf::CircleShape& getBlackHoleShape() const { return m_blackHoleShape; }

private:
	sf::CircleShape m_blackHoleShape;

	float m_centerAttractionForce { 0.f };
};
