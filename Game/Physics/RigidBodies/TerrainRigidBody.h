#pragma once

#include "Game/Physics/IRigidBody.h"
#include "SFML/Graphics/CircleShape.hpp"

class TerrainRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(TerrainRigidBody, IRigidBody)

public:
	TerrainRigidBody(const PhysicsProperties& properties);
	~TerrainRigidBody() override = default;

	void step(const float& deltaTime) override;
};
