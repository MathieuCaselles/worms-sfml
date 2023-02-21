#include "PCFallingCircle.h"

#include "FallingCircleRB.h"

void PCFallingCircle::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& fallingCircle = reinterpret_cast<FallingCircleRB&>(gameObject);

}