#pragma once

#include <Engine/Components/InputComponent.h>

struct ICPlayer : Engine::IInputComponent
{
	ICPlayer();
	void processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene) override;
};