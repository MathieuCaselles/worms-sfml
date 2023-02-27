#pragma once

#include <functional>
#include <Engine/GameObject/GameObject.h>

#include <Game/Components/InputComponents/UI/Buttons/ICButton.h>
#include <Game/Components/PhysicsComponents/UI/Buttons/PCButton.h>
#include <Game/Components/GraphicsComponents/UI/Buttons/GCButton.h>


enum button_states { BUTTON_IDLE = 0, BUTTON_HOVER, BUTTON_PRESSED };


class Button: public Engine::GameObject<ICButton, PCButton, GCButton> {
	friend struct Tools::Factory<Engine::AvailableGameObjectsTypes, true>;
public:
	DECLARE_RTTI(Button, Engine::IGameObject)

private:
	Button(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick);
	Button(float x, float y, float width, float height, std::function<void(Button* button)> const& onLeftClick, std::function<void(Button* button)> const& onRightClick);
	Button(float x, float y, float width, float height, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick);
	Button(float x, float y, float width, float height, std::string text, float sizeText, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, std::function<void(Button* button)> const& onLeftClick);

public:
	~Button() = default;

	const int& getButtonState();
	virtual void setButtonState(button_states newState);

	const sf::RectangleShape& getShape();
	sf::RectangleShape& getEditableShape();

	const sf::Text getText();

	const sf::Color& getIdleColor();
	const sf::Color& getHoverColor();
	const sf::Color& getPressedColor();

	void useOnLeftClick();
	void useOnRightClick();

protected:
	void initShape(float x, float y, float width, float height);

	button_states m_buttonState;

	sf::RectangleShape m_shape;
	sf::Text m_text;
	sf::Font m_font;


	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_pressedColor;

	std::function<void(Button* button)> m_callbackOnLeftClick;
	std::function<void(Button* button)> m_callbackOnRightClick;
};



