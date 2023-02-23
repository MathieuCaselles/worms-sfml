#pragma once

#include "GCTerrain.h"
#include "PCTerrain.h"

#include "Engine/GameObject/GameObject.h"
#include "Engine/Utility/CollisionUtils.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Physics/RigidBodies/TerrainRigidBody.h"

class Terrain : public Engine::GameObject<PCTerrain, GCTerrain, ICVoid>,
			      public TerrainRigidBody
{
	friend GCTerrain;
	friend PCTerrain;

public:
	Terrain(const PhysicsProperties& physicsProperties);
	void onBeginPlay(Engine::IScene& scene) override;

	void generateTerrain(const sf::Vector2f& windowSize);

	const std::vector<sf::Vector2f>& getFloorEdges() const { return m_terrainTopLines; }

private:
	sf::Vector2f m_renderWindowSize;

	// ---- Base image processing
	sf::Image m_baseImageTerrain;
	sf::Color m_imageHeightMapColor;

	// ---- Final convex shape
	std::vector<sf::Vector2f> m_terrainTopLines;
	std::vector<sf::VertexArray> m_triangles;

	// ---- Collision debug
	sf::RectangleShape m_hitSurfaceNormalLine;

	void getAllVertexPointsFromBaseImage(std::vector<sf::Vector2f>& allVertexPoints) const;
	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const;
};
