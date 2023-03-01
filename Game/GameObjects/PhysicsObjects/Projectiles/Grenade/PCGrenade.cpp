#include "PCGrenade.h"

#include "Grenade.h"

#include "Game/Scenes/MainGameScene.h"

void PCGrenade::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& grenade = reinterpret_cast<Grenade&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	grenade.m_circleShape.setPosition(grenade.m_rbPosition);
	grenade.m_circleShape.setRotation(grenade.m_rbRotation);
}
