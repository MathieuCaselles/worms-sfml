#include "GCGrenade.h"

#include "Grenade.h"

void GCGrenade::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& grenade = reinterpret_cast<Grenade&>(gameObject);

	window.draw(grenade.m_circleShape);
}
