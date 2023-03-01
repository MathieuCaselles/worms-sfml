#include "PCCircleExplosion.h"

#include "CircleExplosion.h"

#include "Game/Scenes/MainGameScene.h"

void PCCircleExplosion::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& circleExplosion = reinterpret_cast<CircleExplosion&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	circleExplosion.m_explosionCircleShape.setPosition(circleExplosion.m_rbPosition);
	circleExplosion.m_explosionCircleShape.setRotation(circleExplosion.m_rbRotation);
}
