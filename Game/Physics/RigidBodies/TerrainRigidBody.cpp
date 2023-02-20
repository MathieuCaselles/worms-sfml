#include "TerrainRigidBody.h"

TerrainRigidBody::TerrainRigidBody(const PhysicsProperties& properties)
	: IRigidBody(properties)
{ }

void TerrainRigidBody::step(const float& deltaTime)
{
	IRigidBody::step(deltaTime);
}
