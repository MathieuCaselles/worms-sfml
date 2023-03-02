#include "GCCircleExplosion.h"

#include "CircleExplosion.h"

void GCCircleExplosion::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& circleExplosion = reinterpret_cast<CircleExplosion&>(gameObject);

	window.draw(circleExplosion.m_explosionCircleShape);
	window.draw(circleExplosion.m_spriteExplosionFX);
}
