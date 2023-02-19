#include "PCFallingCircle.h"

#include "FallingCircle.h"

PCFallingCircle::PCFallingCircle()
{ }

void PCFallingCircle::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& fallingCircle = reinterpret_cast<FallingCircle&>(gameObject);

	fallingCircle.m_circleShape.setPosition(fallingCircle.m_rbPosition);
}