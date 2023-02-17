#pragma once

#include "GCTerrain.h"
#include "PCTerrain.h"

#include "Engine/GameObject/GameObject.h"
#include "Engine/Utility/CollisionUtils.h"
#include "Game/Components/InputComponents/ICVoid.h"

constexpr float TERRAIN_DEBUG_MOUSE_RADIUS = 20;

class Terrain : public Engine::GameObject<PCTerrain, GCTerrain, ICVoid>
{
	friend GCTerrain;
	friend PCTerrain;

public:
	using Point2D = sf::Vector2f;

	Terrain();
	void onBeginPlay(Engine::IScene& scene) override;

	void generateTerrain(const sf::Vector2f& windowSize);

	bool IsHit() const { return m_isHit; }
	bool collisionWithCircle(const sf::Vector2f& circlePos, float circleRadius, CollisionUtils::HitResult& impactPoint) const;

private:
	sf::Vector2f m_renderWindowSize;

	// ---- Base image processing
	sf::Image m_baseImageTerrain;
	sf::Color m_imageHeightMapColor;

	// ---- Final convex shape
	std::vector<sf::Vector2f> m_terrainTopLines;
	std::vector<int> m_trianglesVertices;
	std::vector<sf::VertexArray> m_triangles;

	// ---- Collision debug
	bool m_isHit{ false };
	sf::RectangleShape m_hitSurfaceNormalLine;

	void getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints) const;
	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const;
};
