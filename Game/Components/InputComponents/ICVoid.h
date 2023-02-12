#pragma once


#include <Engine/Components/InputComponent.h>


struct ICVoid : Engine::IInputComponent
{
	ICVoid();
	void processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene) override;
};

