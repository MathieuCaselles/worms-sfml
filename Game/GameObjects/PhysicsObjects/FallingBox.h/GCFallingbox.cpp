#include "GCFallingBox.h"

#include "FallingBoxRB.h"

void GCFallingBox::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& fallingBox = reinterpret_cast<FallingBoxRB&>(gameObject);

	window.draw(fallingBox.m_rectangleShape);
}