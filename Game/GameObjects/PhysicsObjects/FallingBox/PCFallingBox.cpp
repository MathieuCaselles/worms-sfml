#include "PCFallingBox.h"

#include "FallingBox.h"

void PCFallingBox::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& fallingBox = reinterpret_cast<FallingBox&>(gameObject);

}