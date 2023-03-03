#include "ICButton.h"

#include <Engine/Scene/Scene.h>
#include <Game/GameObjects/UI/Buttons/Button.h>

ICButton::ICButton()
{
}

void ICButton::processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene)
{
	Button& button = reinterpret_cast<Button&>(gameObject);

	
	button.setButtonState(BUTTON_IDLE);

	sf::RectangleShape& buttonShape = button.getEditableShape();

	if (buttonShape.getGlobalBounds().contains(scene.getMousePositionView()))
	{
		button.setButtonState(BUTTON_HOVER);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			button.setButtonState(BUTTON_PRESSED);
		}
	}

}
