#include "PCFallingCircle.h"

#include "FallingCircle.h"

void PCFallingCircle::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& fallingCircle = reinterpret_cast<FallingCircle&>(gameObject);

}