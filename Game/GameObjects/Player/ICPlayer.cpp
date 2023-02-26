#include "ICPlayer.h"

#include <Engine/Scene/Scene.h>
#include "Player.h"

ICPlayer::ICPlayer()
{
}

void ICPlayer::processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene)
{
	Player& button = reinterpret_cast<Player&>(gameObject);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		button.setButtonState(BUTTON_LEFT);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		button.setButtonState(BUTTON_RIGHT);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		button.setButtonState(BUTTON_JUMP);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		button.setButtonState(BUTTON_LEFTCLICK);
	}
	
}
