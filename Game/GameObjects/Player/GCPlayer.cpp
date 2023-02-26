#include "GCPlayer.h"

#include "Player.h"

void GCPlayer::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& player = reinterpret_cast<Player&>(gameObject);
}