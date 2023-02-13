#pragma once

#include <SFML/Graphics.hpp>

class Terrain
{
public:
	using Point2D = sf::Vector2f;

	Terrain(sf::RenderWindow& renderWindow);

	void draw();

private:
	sf::RenderWindow& _renderWindow;

	// ---- Base image processing
	sf::Image _baseImageTerrain;
	sf::Color _imageHeightMapColor;

	// ---- Final convex shape
	std::vector<int> _trianglesVertices;
	std::vector<sf::VertexArray> _triangles;

	void getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints) const;
	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const;
};
