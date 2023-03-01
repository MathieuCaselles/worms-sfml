#include "ICPlayer.h"

#include <Engine/Scene/Scene.h>
#include "Player.h"

ICPlayer::ICPlayer()
{
}

void ICPlayer::processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene)
{
	Player& player = reinterpret_cast<Player&>(gameObject);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		player.setButtonState(BUTTON_LEFT);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player.setButtonState(BUTTON_RIGHT);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player.setButtonState(BUTTON_JUMP);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		player.setButtonState(BUTTON_LEFTCLICK);
	} else
	{
		player.setButtonState(BUTTON);
	}
	
}
