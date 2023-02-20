#include "TerrainRigidBody.h"

TerrainRigidBody::TerrainRigidBody(TerrainRB& terrain, const PhysicsProperties& properties)
	: IRigidBody(properties), m_terrain(terrain)
{ }

void TerrainRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);
}
