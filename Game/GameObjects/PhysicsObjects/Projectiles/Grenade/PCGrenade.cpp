#include "PCGrenade.h"

#include "Grenade.h"

#include "Game/Scenes/MainGameScene.h"

void PCGrenade::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& grenade = reinterpret_cast<Grenade&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	grenade.m_circleShape.setPosition(grenade.m_rbPosition);
	grenade.m_circleShape.setRotation(grenade.m_rbRotation);

	grenade.m_circleExplosion->setPosition(grenade.m_rbPosition);
	grenade.m_circleExplosion->setRotation(grenade.m_rbRotation);

	grenade.m_currentTime += deltaTime;

	if (grenade.m_currentTime > grenade.m_durationBeforeExplosion)
	{
		grenade.m_currentTime = 0;
		grenade.startExplosion();
	}
}
