#pragma once

#include "GCTerrain.h"

#include "Engine/GameObject/GameObject.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Components/PhysicsComponents/PCVoid.h"

class Terrain : public Engine::GameObject<PCVoid, GCTerrain, ICVoid>
{
public:
	using Point2D = sf::Vector2f;

	Terrain();
	void generateTerrain(const sf::Vector2f& windowSize);

	const std::vector<sf::VertexArray>& getTriangles() const { return m_triangles; }

private:
	//const sf::RenderWindow& _renderWindow;
	sf::Vector2f m_renderWindowSize;

	// ---- Base image processing
	sf::Image m_baseImageTerrain;
	sf::Color m_imageHeightMapColor;

	// ---- Final convex shape
	std::vector<int> m_trianglesVertices;
	std::vector<sf::VertexArray> m_triangles;

	void getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints) const;
	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const;
};
