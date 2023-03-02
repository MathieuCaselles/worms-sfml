#include "PCButton.h"

#include <Game/GameObjects/UI/Buttons/Button.h>

PCButton::PCButton()
{
}

void PCButton::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	Button& button = static_cast<Button&>(gameObject);

	if (button.getButtonState() == BUTTON_PRESSED && button.m_buttonPreviousState == BUTTON_HOVER)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			button.useOnLeftClick();
		else 
			button.useOnRightClick();
	}

	if (button.getButtonState() == BUTTON_HOVER && button.m_buttonPreviousState == BUTTON_IDLE)
	{
		button.useOnMouseEnter();
	}
	if (button.getButtonState() == BUTTON_IDLE && button.m_buttonPreviousState != BUTTON_IDLE)
	{
		button.useOnMouseExit();
	}

	button.m_buttonPreviousState = button.m_buttonState;
}
