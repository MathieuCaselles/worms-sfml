#include "CircleRigidBody.h"

#include "Engine/Utility/MathUtils.h"

CircleRigidBody::CircleRigidBody(const float circleRadius, const PhysicsProperties& properties)
	: IRigidBody(properties)
{
	if(m_properties.m_mass > 0.000001f)
	{
		const float surfaceArea = circleRadius * circleRadius * MathUtils::PI;
		m_properties.m_mass = surfaceArea * m_properties.m_density;
	}
}

void CircleRigidBody::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject,
	Engine::IScene& scene)
{
	IRigidBody::updateImplementation(deltaTime, gameObject, scene);
}
