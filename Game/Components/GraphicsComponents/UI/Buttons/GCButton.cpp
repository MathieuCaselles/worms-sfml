#include "GCButton.h"

#include <Game/GameObjects/UI/Buttons/Button.h>
#include <iostream>

GCButton::GCButton()
{
}

void GCButton::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	Button& button = reinterpret_cast<Button&>(gameObject);

	window.draw(button.getShape());
	window.draw(button.getText());
}
