#pragma once

#include "IRigidBody.h"
#include "SFML/Graphics/RectangleShape.hpp"

struct PhysicsProperties;

class BoxRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(BoxRigidBody, IRigidBody)

public:
	BoxRigidBody(sf::RectangleShape& rectangleShape, const PhysicsProperties& properties);
	BoxRigidBody(const BoxRigidBody& boxRb) = default;
	~BoxRigidBody() override = default;

	void step(const float& deltaTime) override;
	void updateMass() override;

	[[nodiscard]] std::vector<sf::Vector2f> getTransformRectPoints() const;

private:
	sf::RectangleShape& m_rectangleCollisionShape;
};
