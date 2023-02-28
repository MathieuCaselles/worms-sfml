#include "PCPlayer.h"
#include "Player.h"
#include "Engine/Utility/VectorUtils.h"
#include "Game/Assets/GameColors.h"
#include "Game/GameObjects/PhysicsObjects/Projectiles/Grenade/Grenade.h"
#include "Game/Scenes/MainGameScene.h"

void PCPlayer::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& player = reinterpret_cast<Player&>(gameObject);
	// auto& currentScene = reinterpret_cast<MainGameScene&>(scene);
	// player.addForce()
	// currentScene.getPhysics().getAllRigidBodies();

	// TODO: make move here
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
		// TODO:Make jump
		player.addForce({ 0.f,-3000.f });

		//player.m_rbPosition.y -= 1000.f * deltaTime;
		break;

	case BUTTON_LEFTCLICK:
		// TODO: Make shoot
		{
			sf::CircleShape grenadeShape(15);
			grenadeShape.setFillColor(GameColors::iron);
			grenadeShape.setOutlineColor(sf::Color::Black);
			grenadeShape.setOutlineThickness(2);

			PhysicsProperties physicsProperties(4.f, 0.3f);

			//auto grenade = Engine::GameObjectFactory::create<Grenade>(
			//	grenadeShape,
			//	physicsProperties,
			//	sf::Vector2f(player.getPosition().x, player.getPosition().y - 100.f),
			//	sf::Vector2f(10.f * VectorUtils::Normalize(static_cast<sf::Vector2f>(scene.getMousePositionScreen()) - player.getPosition())));

			//scene.getPhysicsWorld().addRigidBody(*grenade);
			//scene.addGameObjects(std::move(grenade));

		}
		break;

	default:
		break;
	}
}
