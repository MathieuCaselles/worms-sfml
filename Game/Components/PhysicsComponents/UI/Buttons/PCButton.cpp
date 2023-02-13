#include "PCButton.h"

#include <Game/GameObjects/UI/Buttons/Button.h>

PCButton::PCButton() : m_callbackIsCalled(false)
{
}

void PCButton::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	Button& button = reinterpret_cast<Button&>(gameObject);

	if (button.getButtonState() == BUTTON_PRESSED && !m_callbackIsCalled)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			button.useOnLeftClick();
		}
		else 
		{
			button.useOnRightClick();
		}
		m_callbackIsCalled = true;
	}
	else if (button.getButtonState() != BUTTON_PRESSED && m_callbackIsCalled) {
		m_callbackIsCalled = false;
	}

}
