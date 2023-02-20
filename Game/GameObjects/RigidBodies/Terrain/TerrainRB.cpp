#include "TerrainRB.h"

#include <iostream>
#include <random>

#include "Engine/Utility/PolygonHelper.h"
#include "Game/Assets/GameColors.h"

constexpr int NUM_VERTEX_FOR_BASE_IMAGE = 30;
constexpr sf::Uint8 HEIGHT_MAP_COLOR_INCERTITUDE = 40;

TerrainRB::TerrainRB(const PhysicsProperties& physicsProperties) :
	TerrainRigidBody(*this, physicsProperties),
	m_imageHeightMapColor(GameColors::terrainHeightMap)
{
	// ---- Base image loading
	if (!m_baseImageTerrain.loadFromFile("./Assets/Maps/BaseTerrain4.png"))
	{
		std::cout << "Can not load terrain image !" << std::endl;
		return;
	}
}

void TerrainRB::onBeginPlay(Engine::IScene& scene)
{
	GameObject<PCTerrain, GCTerrain, ICVoid>::onBeginPlay(scene);

	m_hitSurfaceNormalLine.setSize(sf::Vector2f(5, 80));
	m_hitSurfaceNormalLine.setFillColor(sf::Color::Green);
	m_hitSurfaceNormalLine.setOrigin(m_hitSurfaceNormalLine.getSize().x / 2, m_hitSurfaceNormalLine.getSize().y); // Bottom-centered
}

void TerrainRB::generateTerrain(const sf::Vector2f& windowSize)
{
	if (windowSize.x < 1 || windowSize.y < 1)
		return;

	m_renderWindowSize = windowSize;
	getAllVertexPointsFromBaseImage(m_terrainTopLines);

	// -------- Convex shape construction
	std::vector<sf::Vector2f> allTerrainVertexPoints;
	allTerrainVertexPoints.reserve(NUM_VERTEX_FOR_BASE_IMAGE + 4); // 2 for screen edges, 2 other for terrain sides.

	allTerrainVertexPoints.emplace_back(0, m_renderWindowSize.y);
	allTerrainVertexPoints.emplace_back(m_renderWindowSize.x, m_renderWindowSize.y);

	for (const auto& topLine : m_terrainTopLines)
	{
		allTerrainVertexPoints.emplace_back(topLine.x, topLine.y);
	}

	// -------- Terrain drawing
	PolygonHelper::triangulate(allTerrainVertexPoints, m_trianglesVertices);

	for (int i = 0; i < static_cast<int>(m_trianglesVertices.size()); i += 3)
	{
		sf::VertexArray newTriangle{ sf::Triangles, 3 };

		newTriangle[0].position = allTerrainVertexPoints[m_trianglesVertices[i]];
		newTriangle[1].position = allTerrainVertexPoints[m_trianglesVertices[i + 1]];
		newTriangle[2].position = allTerrainVertexPoints[m_trianglesVertices[i + 2]];

		const sf::Color randomColor = PolygonHelper::getRandomTerrainColor();

		newTriangle[0].color = randomColor;
		newTriangle[1].color = randomColor;
		newTriangle[2].color = randomColor;

		m_triangles.push_back(newTriangle);
	}
}

void TerrainRB::getAllVertexPointsFromBaseImage(std::vector<sf::Vector2f>& allVertexPoints) const
{
	const auto windowW = static_cast<float>(m_renderWindowSize.x);
	const auto windowH = static_cast<float>(m_renderWindowSize.y);

	const float baseImageWRatio = windowW / static_cast<float>(m_baseImageTerrain.getSize().x);
	const float baseImageHRatio = windowH / static_cast<float>(m_baseImageTerrain.getSize().y);

	for (int i = NUM_VERTEX_FOR_BASE_IMAGE; i >= 0; --i)
	{
		const int col = i * static_cast<int>(m_baseImageTerrain.getSize().x) / NUM_VERTEX_FOR_BASE_IMAGE;

		for (int row = 0; row < static_cast<int>(m_baseImageTerrain.getSize().y); ++row)
		{
			const sf::Color currentPixelColor = m_baseImageTerrain.getPixel(col, row);

			if (isColorIntoColorRange(currentPixelColor, HEIGHT_MAP_COLOR_INCERTITUDE))
			{
				allVertexPoints.emplace_back(static_cast<int>(col * baseImageWRatio), static_cast<int>(row * baseImageHRatio));
				break;
			}
		}
	}
}

bool TerrainRB::isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const
{
	return m_imageHeightMapColor.r <= std::min(255, color.r + incertitude) && m_imageHeightMapColor.r >= std::max(0, color.r - incertitude);
}

