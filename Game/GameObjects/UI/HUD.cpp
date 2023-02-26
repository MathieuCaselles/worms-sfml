#include "HUD.h"

#include "Buttons/Options.h"
#include "Engine/Game/Game.h"

HUD::HUD()
{
	// addGameObjects(new Options(1700, 25, 200, 50, "Options", 30.f,
	// 	sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
	// 	[&](Button* button) {m_window.close(); }));
}

HUD::~HUD()
{
	
}

void HUD::SetButtonOptions()
{
	// add(new Options(1700, 25, 200, 50, "Options", 30.f,
	// 	sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
	// 	[&](Button* button) {m_window.close(); }));
	//
	// add(new Button(1400, 600, 230, 80, "Quitter", 40.f,
	// 	sf::Color(252, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
	// 	[&](Button* button) { m_window.close(); }));
}

void HUD::onBeginPlay(Engine::IScene& scene)
{
	GameObject<PCVoid, GCVoid, ICVoid>::onBeginPlay(scene);

	// add(new Options(1700, 25, 200, 50, "Options", 30.f,
	// 	sf::Color(250, 79, 36), sf::Color(255, 120, 70), sf::Color(200, 79, 36),
	// 	[&](Button* button) {scene.getWindow().close(); }));
}

