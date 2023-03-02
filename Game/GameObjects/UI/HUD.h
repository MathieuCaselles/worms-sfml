#pragma once

#include <Engine/GameObject/GameObject.h>
#include <Engine/Scene/Scene.h>


#include <Game/Components/InputComponents/ICVoid.h>
#include <Game/Components/PhysicsComponents/PCVoid.h>
#include <Game/Components/GraphicsComponents/GCVoid.h>

class MainGameScene;
class Button;

class HUD : public Engine::GameObject<PCVoid, GCVoid, ICVoid> {
public:
	DECLARE_RTTI(HUD, Engine::IGameObject)

public:
	HUD();
	~HUD();

	void onBeginPlay(Engine::IScene& scene) override;

protected:
	MainGameScene* p_scene;

	std::unique_ptr<Button> p_ButtonGrenade;
	std::unique_ptr<Button> p_ButtonBanana;
	std::unique_ptr<Button> p_ButtonBlackHole;
};



