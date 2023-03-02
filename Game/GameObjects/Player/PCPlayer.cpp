#include "PCPlayer.h"
#include "Player.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"
#include "Game/Scenes/MainGameScene.h"

void PCPlayer::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& player = reinterpret_cast<Player&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	if (player.getCanPlay())
	{
		switch (player.m_inputState)
		{
		case RIGHT:
			if (player.m_rbPosition.x < 1880)
				player.m_rbPosition.x += player.m_movementSpeed * deltaTime;
			
			player.m_playerShape.setScale(-1.f, 1.f);
			break;

		case LEFT:
			if (player.m_rbPosition.x > 40)
				player.m_rbPosition.x -= player.m_movementSpeed * deltaTime;

			player.m_playerShape.setScale(1.f, 1.f);
			break;

		case JUMP:

			break;

		case CLICK:
			{
				// TODO: Make shoot
				currentScene.m_hasPlayed = true;

				const auto grenadeSpawnPoint = sf::Vector2f(player.getPosition().x, player.getPosition().y - 80.f);

				currentScene.spawnGrenade(
					grenadeSpawnPoint,
					VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionScreen()) - grenadeSpawnPoint)
				);

				break;
			}

		default:
			break;
		}
	}

	player.m_playerShape.setPosition(player.m_rbPosition);
	player.m_playerShape.setRotation(player.m_rbRotation);
}
