#include "GCFallingCircle.h"

#include "FallingCircleRB.h"

void GCFallingCircle::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& fallingCircle = reinterpret_cast<FallingCircleRB&>(gameObject);

	window.draw(fallingCircle.m_circleShape);
}