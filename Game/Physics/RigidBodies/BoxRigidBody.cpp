#include "BoxRigidBody.h"


BoxRigidBody::BoxRigidBody(const sf::Vector2f& boxBounds, const PhysicsProperties& properties)
	: IRigidBody(properties)
{
	if (m_properties.m_mass < 0.000001f)
	{
		const float surfaceArea = boxBounds.x * boxBounds.y;
		m_properties.m_mass = surfaceArea * m_properties.m_density;
	}
}

void BoxRigidBody::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	IRigidBody::updateImplementation(deltaTime, gameObject, scene);
}
