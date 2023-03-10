#pragma once


#include <Engine/Components/InputComponent.h>

struct ICButton : Engine::IInputComponent 
{
	ICButton();
	void processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene) override;
};

