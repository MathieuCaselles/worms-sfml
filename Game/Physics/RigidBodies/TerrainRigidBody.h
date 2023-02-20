#pragma once

#include "Game/Physics/IRigidBody.h"
#include "SFML/Graphics/CircleShape.hpp"

class TerrainRB;

class TerrainRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(TerrainRigidBody, IRigidBody)

public:
	TerrainRigidBody(TerrainRB& terrain, const PhysicsProperties& properties);
	~TerrainRigidBody() override = default;

	void step(const float& deltaTime) override;

	[[nodiscard]] const TerrainRB& getTerrain() const { return m_terrain; }

private:
	TerrainRB& m_terrain;
};
