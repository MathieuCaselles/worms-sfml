#pragma once

#include "GCTerrain.h"

#include "Engine/GameObject/GameObject.h"
#include "Game/Components/InputComponents/ICVoid.h"
#include "Game/Components/PhysicsComponents/PCVoid.h"

class Terrain : public Engine::GameObject<PCVoid, GCTerrain, ICVoid>
{
public:
	using Point2D = sf::Vector2f;

	//Terrain(const sf::RenderWindow& renderWindow);1920, 1080
	Terrain(const sf::Vector2f& renderWindowSize);

	const std::vector<sf::VertexArray>& getTriangles() const { return _triangles; }

private:
	//const sf::RenderWindow& _renderWindow;
	sf::Vector2f _renderWindowSize;

	// ---- Base image processing
	sf::Image _baseImageTerrain;
	sf::Color _imageHeightMapColor;

	// ---- Final convex shape
	std::vector<int> _trianglesVertices;
	std::vector<sf::VertexArray> _triangles;

	void getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints) const;
	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const;
};
