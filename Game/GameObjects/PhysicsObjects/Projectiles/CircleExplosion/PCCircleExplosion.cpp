#include "PCCircleExplosion.h"

#include "CircleExplosion.h"

#include "Game/Scenes/MainGameScene.h"

void PCCircleExplosion::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& circleExplosion = reinterpret_cast<CircleExplosion&>(gameObject);
	auto& currentScene = reinterpret_cast<MainGameScene&>(scene);

	circleExplosion.m_explosionCircleShape.setPosition(circleExplosion.m_rbPosition);
	circleExplosion.m_explosionCircleShape.setRotation(circleExplosion.m_rbRotation);
	circleExplosion.m_spriteExplosionFX.setPosition(circleExplosion.m_rbPosition.x - circleExplosion.m_spriteExplosionFX.getGlobalBounds().width / 2.f,
		circleExplosion.m_rbPosition.y - circleExplosion.m_spriteExplosionFX.getGlobalBounds().height / 2.f);

	circleExplosion.m_currentTime += deltaTime;

	if (circleExplosion.m_currentTime > circleExplosion.m_durationExplosion)
	{
		circleExplosion.m_currentTime = 0;
		circleExplosion.m_rectSourceSprite.left = 0;
		circleExplosion.setIsActive(false);
		circleExplosion.getPhysicsProperties().m_isActive = false;
	}
	circleExplosion.tryToPlayExplosionFX();
	if (circleExplosion.getCanPlayExplosionFX())
		currentScene.playExplosionSound();
}
