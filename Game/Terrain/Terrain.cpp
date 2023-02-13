#include "Terrain.h"

#include <iostream>
#include <random>

#include "Engine/PolygonHelper.h"

constexpr int NUM_VERTEX_FOR_BASE_IMAGE = 10;
constexpr sf::Uint8 HEIGHT_MAP_COLOR_INCERTITUDE = 40;

Terrain::Terrain(sf::RenderWindow& renderWindow) :
	_renderWindow(renderWindow),
	_imageHeightMapColor(sf::Color::Red)
{
	// ---- Base image loading
	if (!_baseImageTerrain.loadFromFile("./Assets/Maps/BaseTerrain4.png"))
	{
		std::cout << "Can not load terrain image !" << std::endl;
		return;
	}

	// -------- Convex shape construction
	std::vector<Point2D> allTerrainVertexPoints;
	allTerrainVertexPoints.reserve(NUM_VERTEX_FOR_BASE_IMAGE + 4); // 2 for screen edges, 2 other for terrain sides.

	allTerrainVertexPoints.emplace_back(0, _renderWindow.getSize().y);
	allTerrainVertexPoints.emplace_back(_renderWindow.getSize().x, _renderWindow.getSize().y);
	getAllVertexPointsFromBaseImage(allTerrainVertexPoints);

	// -------- Terrain drawing
	PolygonHelper::triangulate(allTerrainVertexPoints, _trianglesVertices);

	for (int i = 0; i < _trianglesVertices.size(); i += 3)
	{
		sf::VertexArray newTriangle{ sf::Triangles, 3 };

		newTriangle[0].position = allTerrainVertexPoints[_trianglesVertices[i]];
		newTriangle[1].position = allTerrainVertexPoints[_trianglesVertices[i+1]];
		newTriangle[2].position = allTerrainVertexPoints[_trianglesVertices[i+2]];

		const sf::Color randomColor = PolygonHelper::getRandomTerrainColor();

		newTriangle[0].color = randomColor;
		newTriangle[1].color = randomColor;
		newTriangle[2].color = randomColor;

		_triangles.push_back(newTriangle);
	}
}

void Terrain::draw()
{
	for (const auto& triangle : _triangles)
	{
		_renderWindow.draw(triangle);
	}
}

void Terrain::getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints) const
{
	const float windowW = static_cast<float>(_renderWindow.getSize().x);
	const float windowH = static_cast<float>(_renderWindow.getSize().y);

	const float baseImageWRatio = windowW / static_cast<float>(_baseImageTerrain.getSize().x);
	const float baseImageHRatio = windowH / static_cast<float>(_baseImageTerrain.getSize().y);

	for (int i = NUM_VERTEX_FOR_BASE_IMAGE; i >= 0; --i)
	{
		const int col = i * static_cast<int>(_baseImageTerrain.getSize().x) / NUM_VERTEX_FOR_BASE_IMAGE;

		for (int row = 0; row < static_cast<int>(_baseImageTerrain.getSize().y); ++row)
		{
			const sf::Color currentPixelColor = _baseImageTerrain.getPixel(col, row);

			if (isColorIntoColorRange(currentPixelColor, HEIGHT_MAP_COLOR_INCERTITUDE))
			{
				allVertexPoints.emplace_back(static_cast<int>(col * baseImageWRatio), static_cast<int>(row * baseImageHRatio));
				break;
			}
		}
	}
}

bool Terrain::isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude) const
{
	return _imageHeightMapColor.r <= std::min(255, color.r + incertitude) && _imageHeightMapColor.r >= std::max(0, color.r - incertitude);
}

