#include "PCTerrain.h"

#include "Terrain.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/VectorUtils.h"

PCTerrain::PCTerrain() : m_callbackIsCalled(false)
{
}

void PCTerrain::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& terrain = reinterpret_cast<Terrain&>(gameObject);

	const auto mousePosition = static_cast<sf::Vector2f>(scene.getMousePositionScreen());

	CollisionUtils::HitResult hitResult;
	terrain.m_isHit = terrain.collisionWithCircle(mousePosition, TERRAIN_DEBUG_MOUSE_RADIUS, hitResult);

	if (terrain.m_isHit)
	{
		// Set debug normal line transform
		terrain.m_hitSurfaceNormalLine.setPosition(hitResult.impactPoint.x, hitResult.impactPoint.y);

		const auto lineDirection = sf::Vector2f(0, terrain.m_hitSurfaceNormalLine.getSize().y);
		float lineAngle = VectorUtils::GetAngle(VectorUtils::Normalize(lineDirection), hitResult.normal);

		lineAngle = hitResult.normal.x > 0 ? -lineAngle : lineAngle;

		terrain.m_hitSurfaceNormalLine.setRotation(lineAngle);
	}
}