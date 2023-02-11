#pragma once

#include <SFML/Graphics.hpp>

constexpr int NUM_VERTEX_FOR_BASE_IMAGE = 30;
constexpr sf::Uint8 HEIGHT_MAP_COLOR_INCERTITUDE = 40;

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
	//std::vector<Point2D> _allTerrainVertexPoints;

	sf::ConvexShape _convexShapeTerrain;


	std::vector<Point2D> getAllVertexPointsFromBaseImage();
	sf::Vector2f getEdgeFromPoints(const Point2D& pointA, const Point2D& pointB);

	bool isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude);
};
