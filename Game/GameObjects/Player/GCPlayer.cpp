#include "GCPlayer.h"

#include "Player.h"

void GCPlayer::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& player = reinterpret_cast<Player&>(gameObject);

	window.draw(player.m_playerShape);
	window.draw(player.m_currentHealthText);
}