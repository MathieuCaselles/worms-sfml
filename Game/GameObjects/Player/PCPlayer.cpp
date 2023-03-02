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

				const auto spawnPoint = sf::Vector2f(player.getPosition().x, player.getPosition().y - 80.f);

				switch(player.m_skillState)
				{
		
					case BANANA: {
						if (const int numberBanana = player.getNumberBanana(); numberBanana > 0)
						{
							player.setNumberBanana(numberBanana-1);
							currentScene.spawnFragBall(
								spawnPoint,
								VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionWindow()) - spawnPoint)
							);
						}
					} break;
					case BLACK_HOLE: {
						if (const int numberBlackHole = player.getNumberBlackHole(); numberBlackHole > 0)
						{
							player.setNumberBlackHole(numberBlackHole - 1);
							currentScene.spawnBlackHole(
								static_cast<sf::Vector2f>(scene.getMousePositionWindow())
							);
						}
					} break;

					default: {
						currentScene.spawnGrenade(
							spawnPoint,
							VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionWindow()) - spawnPoint)
						);
					} break;


				}



				break;
			}

		default:
			break;
		}
	}

	player.m_playerShape.setPosition(player.m_rbPosition);
	player.m_playerShape.setRotation(player.m_rbRotation);
}
