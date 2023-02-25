#include "HUD.h"

#include "Engine/Game/Game.h"

HUD::HUD()
{

	addGameObjects(new Options(1700, 25, 200, 50, "Options", 30.f,
		sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
		[&](Options* button) {m_window.close(); }));
}

HUD::~HUD()
{
	
}

void HUD::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& hud = reinterpret_cast<HUD&>(gameObject);

}