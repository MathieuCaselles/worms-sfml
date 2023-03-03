#pragma once


#include <Engine/Components/PhysicsComponent.h>


struct PCVoid : Engine::IPhysicsComponent
{
	PCVoid();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;

private:
	bool m_callbackIsCalled;
};

