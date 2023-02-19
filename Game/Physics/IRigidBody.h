#pragma once

#include "Engine/Components/PhysicsComponent.h"
#include "PhysicsProperties.h"

class IRigidBody : public Engine::IPhysicsComponent
{
protected:
	explicit IRigidBody(const PhysicsProperties& properties)
		: m_properties(properties) { }

	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override
	{
		
	}

	sf::Vector2f m_velocity;

	float m_rotationAngle { 0.f };
	float m_angularVelocity { 0.f };

	PhysicsProperties m_properties;
};