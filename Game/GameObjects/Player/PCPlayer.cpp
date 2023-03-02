#include "PCPlayer.h"
#include "Player.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"
#include "Game/Scenes/MainGameScene.h"

void PCPlayer::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& player = reinterpret_cast<Player&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	player.m_playerShape.setPosition(player.m_rbPosition);

	// player.addForce()
	// currentScene.getPhysics().getAllRigidBodies();

	// TODO: make move here
	switch (player.m_inputState)
	{
	case BUTTON_RIGHT:
		player.m_rbPosition.x += 150 * deltaTime;
		//player.addForce({ 6000.f,0.f });
		player.m_playerShape.setScale(-1.f, 1.f);
		break;

	case BUTTON_LEFT:
		player.m_rbPosition.x -= 150 * deltaTime;
		player.m_playerShape.setScale(1.f, 1.f);
		break;

	case BUTTON_JUMP:
		// TODO:Make jump
		player.addForce({ 0.f,-3000.f });

		//player.m_rbPosition.y -= 1000.f * deltaTime;
		break;

	case BUTTON_LEFTCLICK:
		// TODO: Make shoot
		{
			const auto grenadeSpawnPoint = sf::Vector2f(player.getPosition().x, player.getPosition().y - 80.f);

			currentScene.spawnGrenade(
				grenadeSpawnPoint,
				VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionScreen()) - grenadeSpawnPoint)
			);

		}
		break;

	default:
		break;
	}
}
