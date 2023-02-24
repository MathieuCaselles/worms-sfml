#include "GCFallingBox.h"

#include "FallingBox.h"

void GCFallingBox::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& fallingBox = reinterpret_cast<FallingBox&>(gameObject);

	window.draw(fallingBox.m_rectangleShape);
}