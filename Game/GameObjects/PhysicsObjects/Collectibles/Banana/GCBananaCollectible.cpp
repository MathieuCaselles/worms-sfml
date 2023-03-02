#include "GCBananaCollectible.h"

#include "BananaCollectible.h"

void GCBananaCollectible::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& collectible = reinterpret_cast<BananaCollectible&>(gameObject);

	window.draw(collectible.m_bananaShape);
}
