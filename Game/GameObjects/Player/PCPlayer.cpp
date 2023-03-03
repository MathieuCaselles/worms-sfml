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
							currentScene.playShootSound();
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
							currentScene.playBlackHoleSound();
						}
					} break;

					default: {
						currentScene.spawnGrenade(
							spawnPoint,
							VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionWindow()) - spawnPoint)
						);
						currentScene.playShootSound();
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

	auto thirdOfLife = player.m_maxHealth / 3;
	auto twoThirdOfLife = player.m_maxHealth - thirdOfLife;



	if (player.m_health < twoThirdOfLife)
	{
		if (player.m_health < thirdOfLife)
			player.m_currentHealthText.setFillColor(sf::Color(255, 0, 0));
		else
			player.m_currentHealthText.setFillColor(sf::Color(255, 181, 54));
	}

	player.m_currentHealthText.setPosition(player.m_rbPosition + sf::Vector2f(-35.f, -80.f ));
	player.m_currentHealthText.setString(std::to_string(player.m_health));
}
