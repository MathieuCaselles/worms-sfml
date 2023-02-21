#pragma once

#include "Game/Physics/RigidBodies/IRigidBody.h"

#include "SFML/Graphics/RectangleShape.hpp"

struct PhysicsProperties;

class BoxRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(BoxRigidBody, IRigidBody)

public:
	BoxRigidBody(sf::RectangleShape& rectangleShape, const PhysicsProperties& properties);
	~BoxRigidBody() override = default;

	void step(const float& deltaTime) override;

	[[nodiscard]] std::vector<sf::Vector2f> getTransformRectPoints() const;

private:
	sf::RectangleShape& m_rectangleShape;
};
