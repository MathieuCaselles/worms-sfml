#include "HUD.h"

#include "Engine/Game/Game.h"
#include "../../Scenes/MainGameScene.h"
#include <Game/GameObjects/UI/Buttons/Button.h>
#include <Game/GameObjects/Player/Player.h>

HUD::HUD(): p_scene(nullptr)
{

}

HUD::~HUD()
{
	
}


void HUD::onBeginPlay(Engine::IScene& scene)
{
	MainGameScene* gameScene = static_cast<MainGameScene*>(&scene);

	if (gameScene == nullptr)
		return;

	p_scene = gameScene;

	p_ButtonGrenade = Engine::GameObjectFactory::create<Button>(400, 25, 200, 50, "Grenade", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {
			if (p_scene->isChangeTurn())
				return;

			p_scene->getCurrentPlayer()->setSkillState(GRENADE);
		 });

	p_ButtonBanana = Engine::GameObjectFactory::create<Button>(700, 25, 200, 50, "Banane", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {
			if (p_scene->isChangeTurn())
			return;

			p_scene->getCurrentPlayer()->setSkillState(BANANA);
		});

	p_ButtonBlackHole = Engine::GameObjectFactory::create<Button>(1000, 25, 200, 50, "Trou noir", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Button* button) {
			if (p_scene->isChangeTurn())
			return;

			p_scene->getCurrentPlayer()->setSkillState(BLACK_HOLE);
		});


	add(p_ButtonGrenade.get());
	add(p_ButtonBanana.get());
	add(p_ButtonBlackHole.get());
}

