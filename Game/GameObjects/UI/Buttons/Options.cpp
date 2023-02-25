#include "Options.h"

Options::Options(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick)
	: Button(x, y, width, height, onLeftClick) {
	
}

Options::Options(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick, std::function<void(Button* button)> const& onRightClick)
	: Button(x, y, width, height, onLeftClick, onRightClick) {
	
}

Options::Options(float x, float y, float width, float height, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick)
	: Button(x, y, width, height, text, idleColor, hoverColor, activeColor, onLeftClick) {
	
}

Options::Options(float x, float y, float width, float height, std::string text, float sizeText, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick)
	: Button(x, y, width, height, text, sizeText, idleColor, hoverColor, activeColor, onLeftClick) {
	
}

Options::~Options()
{
	
}