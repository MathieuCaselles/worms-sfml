#include "Terrain.h"

#include <iostream>

#include "Engine/VectorUtils.h"

Terrain::Terrain(sf::RenderWindow& renderWindow) :
	_renderWindow(renderWindow),
	_imageHeightMapColor(sf::Color::Red)
{
	// ---- Base image loading
	if (!_baseImageTerrain.loadFromFile("./Assets/Maps/BaseTerrain.png"))
	{
		std::cout << "Can not load terrain image !" << std::endl;
		return;
	}

	std::vector<Point2D> allTerrainVertexPoints = getAllVertexPointsFromBaseImage();

	// ---- Convex shape construction
	allTerrainVertexPoints.emplace_back(_renderWindow.getSize().x, _renderWindow.getSize().y);
	allTerrainVertexPoints.emplace_back(0, _renderWindow.getSize().y);

	const int terrainPointsCount = static_cast<int>(allTerrainVertexPoints.size());
	_convexShapeTerrain.setPointCount(terrainPointsCount);

	for (int i = 0; i < terrainPointsCount; ++i)
	{
		_convexShapeTerrain.setPoint(i, allTerrainVertexPoints[i]);
	}

	//_convexShapeTerrain.setOrigin(0, _renderWindow.getSize().y);
	_convexShapeTerrain.setFillColor(sf::Color::Red);
}

void Terrain::draw()
{
	_renderWindow.draw(_convexShapeTerrain);
}

std::vector<Terrain::Point2D> Terrain::getAllVertexPointsFromBaseImage()
{
	std::vector<Point2D> allVertexPoints;

	const float baseImageWRatio = _baseImageTerrain.getSize().x / _renderWindow.getSize().x;
	const float baseImageHRatio = _baseImageTerrain.getSize().y / _renderWindow.getSize().y;

	for (int i = 0; i < NUM_VERTEX_FOR_BASE_IMAGE; ++i)
	{
		const float col = i * _baseImageTerrain.getSize().x / NUM_VERTEX_FOR_BASE_IMAGE;

		for (int row = 0; row < _baseImageTerrain.getSize().y; ++row)
		{
			sf::Color currPixelColor = _baseImageTerrain.getPixel(col, row);
			if(currPixelColor != sf::Color::Black)
			{
				int oui = 0;
			}

			if (isColorIntoColorRange(currPixelColor, HEIGHT_MAP_COLOR_INCERTITUDE))
			{
				allVertexPoints.emplace_back(static_cast<int>(col * baseImageHRatio), static_cast<int>(row * baseImageWRatio));
				break;
			}
		}
	}

	return allVertexPoints;
}

sf::Vector2f Terrain::getEdgeFromPoints(const Point2D& pointA, const Point2D& pointB)
{
	return {};
}

bool Terrain::isColorIntoColorRange(const sf::Color& color, sf::Uint8 incertitude)
{
	return _imageHeightMapColor.r <= std::min(255, color.r + incertitude) && _imageHeightMapColor.r >= std::max(0, color.r - incertitude)/* &&
		   _imageHeightMapColor.g <= std::min(255, color.g + incertitude) && _imageHeightMapColor.g >= std::max(0, color.g - incertitude) &&
		   _imageHeightMapColor.b <= std::min(255, color.b + incertitude) && _imageHeightMapColor.b >= std::max(0, color.b - incertitude)*/;
}

