#include "GCBlackHole.h"

#include "BlackHole.h"

void GCBlackHole::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& blackHole = reinterpret_cast<BlackHole&>(gameObject);

	window.draw(blackHole.m_blackHoleShape);
}