#include "PCPlayer.h"
#include "Player.h"
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
				player.m_rbPosition.x += player.m_movement * deltaTime;
			//player.addForce({ 6000.f,0.f });
			player.m_circleShape.setScale(-1.f, 1.f);
			break;

		case LEFT:
			if (player.m_rbPosition.x > 40)
				player.m_rbPosition.x -= player.m_movement * deltaTime;
			player.m_circleShape.setScale(1.f, 1.f);
			break;

		case JUMP:
			
			player.addForce({ 0.f,-3000.f });

			break;

		case CLICK:
			// TODO: Make shoot
			currentScene.m_hasPlayed = true;
			break;

		default:
			break;
		}
	}
}
