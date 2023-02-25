#pragma once

#include <functional>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Scene/Scene.h>

#include <Game/GameObjects/UI/Buttons/Button.h>
#include <Game/GameObjects/UI/Buttons/Options.h>



class HUD : public Engine::GameObject<Engine::IPhysicsComponent> {
public:
	HUD();
	~HUD();
	void updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene) override;

	
};



