#pragma once


#include <Engine/Components/PhysicsComponent.h>


struct PCButton : Engine::IPhysicsComponent
{
	PCButton();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;

private:
};

