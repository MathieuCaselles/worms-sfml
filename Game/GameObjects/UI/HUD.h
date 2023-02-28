#pragma once

#include <functional>
#include <Engine/GameObject/GameObject.h>
#include <Engine/Scene/Scene.h>

#include <Game/GameObjects/UI/Buttons/Button.h>

#include <Game/Components/InputComponents/ICVoid.h>
#include <Game/Components/PhysicsComponents/PCVoid.h>
#include <Game/Components/GraphicsComponents/GCVoid.h>


class HUD : public Engine::GameObject<PCVoid, GCVoid, ICVoid> {
public:
	DECLARE_RTTI(HUD, Engine::IGameObject)

public:
	HUD();
	~HUD();

	void onBeginPlay(Engine::IScene& scene) override;
};



