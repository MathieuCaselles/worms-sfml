#ifndef PCEXAMPLEBUTTON_H
#define PCEXAMPLEBUTTON_H

#include <Engine/Components/PhysicsComponent.h>


struct PCButton : Engine::IPhysicsComponent
{
	PCButton();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;

private:
	bool m_callbackIsCalled;
};

#endif // PCEXAMPLEBUTTON_H