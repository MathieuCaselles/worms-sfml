#include "PCFallingBox.h"

#include "FallingBoxRB.h"

void PCFallingBox::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& fallingBox = reinterpret_cast<FallingBoxRB&>(gameObject);

	fallingBox.m_rectangleShape.setPosition(fallingBox.m_rbPosition);
}