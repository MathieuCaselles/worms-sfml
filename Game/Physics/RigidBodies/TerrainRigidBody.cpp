#include "TerrainRigidBody.h"

#include "Game/GameObjects/PhysicsObjects/Terrain/Terrain.h"

TerrainRigidBody::TerrainRigidBody(Terrain& terrain, const PhysicsProperties& properties)
	: IRigidBody(properties), m_terrain(terrain)
{ }

void TerrainRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);
}

void TerrainRigidBody::updateMass()
{
	IRigidBody::updateMass();
}

const std::vector<sf::Vector2f>& TerrainRigidBody::getEdges() const
{
	return m_terrain.getFloorEdges(); 
}
