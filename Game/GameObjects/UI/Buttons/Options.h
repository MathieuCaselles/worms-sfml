#pragma once

#include <Game/Components/InputComponents/UI/Buttons/ICButton.h>
#include <Game/Components/PhysicsComponents/UI/Buttons/PCButton.h>
#include <Game/Components/GraphicsComponents/UI/Buttons/GCButton.h>
#include <Game/GameObjects/UI/Buttons/Button.h>

class Options : public Button {
public:
	Options(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick)
		: Button(x, y, width, height, onLeftClick) {}
	Options(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick, std::function<void(Button* button)> const& onRightClick)
		: Button(x, y, width, height, onLeftClick, onRightClick) {}
	Options(float x, float y, float width, float height, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick)
		: Button(x, y, width, height, text, idleColor, hoverColor, activeColor, onLeftClick) {}
	Options(float x, float y, float width, float height, std::string text, float sizeText, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick)
		: Button(x, y, width, height, text, sizeText, idleColor, hoverColor, activeColor, onLeftClick) {}
	~Options() override = default;


private:

	
};