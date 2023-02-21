#include "GCFallingCircle.h"

#include "FallingCircle.h"

void GCFallingCircle::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& fallingCircle = reinterpret_cast<FallingCircle&>(gameObject);

	window.draw(fallingCircle.m_circleShape);
}