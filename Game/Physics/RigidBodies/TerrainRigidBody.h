#pragma once

#include <vector>

#include "Game/Physics/RigidBodies/IRigidBody.h"

class Terrain;
struct PhysicsProperties;

class TerrainRigidBody : public IRigidBody
{
public:
	DECLARE_RTTI(TerrainRigidBody, IRigidBody)

public:
	TerrainRigidBody(Terrain& terrain, const PhysicsProperties& properties);
	~TerrainRigidBody() override = default;

	void step(const float& deltaTime) override;
	void updateMass() override;

	[[nodiscard]] const std::vector<sf::Vector2f>& getEdges() const;

private:
	Terrain& m_terrain;
};
