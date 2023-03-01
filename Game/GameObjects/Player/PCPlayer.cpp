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
		case BUTTON_RIGHT:
			player.m_rbPosition.x += 150 * deltaTime;
			//player.addForce({ 6000.f,0.f });
			player.m_circleShape.setScale(-1.f, 1.f);
			break;

		case BUTTON_LEFT:
			player.m_rbPosition.x -= 150 * deltaTime;
			player.m_circleShape.setScale(1.f, 1.f);
			break;

		case BUTTON_JUMP:
			// TODO:Make better jump
			player.addForce({ 0.f,-3000.f });

			break;

		case BUTTON_LEFTCLICK:
			// TODO: Make shoot
			currentScene.m_changeTurn = true;
			std::cout << "clicked" << std::endl;
			break;

		default:
			break;
		}
	}
}
