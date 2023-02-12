#include "Terrain.h"

#include <iostream>
#include <random>

#include "Engine/VectorUtils.h"
#include "Engine/PolygonHelper.h"

constexpr int NUM_VERTEX_FOR_BASE_IMAGE = 100;
constexpr sf::Uint8 HEIGHT_MAP_COLOR_INCERTITUDE = 40;

Terrain::Terrain(sf::RenderWindow& renderWindow) :
	_renderWindow(renderWindow),
	_imageHeightMapColor(sf::Color::Red)
{
	// ---- Base image loading
	if (!_baseImageTerrain.loadFromFile("./Assets/Maps/BaseTerrain3.png"))
	{
		std::cout << "Can not load terrain image !" << std::endl;
		return;
	}
	// -------- Convex shape construction
	std::vector<Point2D> allTerrainVertexPoints;

	allTerrainVertexPoints.emplace_back(0, 0);
	getAllVertexPointsFromBaseImage(allTerrainVertexPoints);
	allTerrainVertexPoints.emplace_back(_renderWindow.getSize().x, 0);

	// ----
	std::vector<Point2D> allTerrainVertexPointsReversed;
	allTerrainVertexPointsReversed.reserve(allTerrainVertexPoints.size() + 2);
	allTerrainVertexPointsReversed.emplace_back(0, _renderWindow.getSize().y);
	for (int i = 0; i < allTerrainVertexPoints.size(); ++i)
	{
		allTerrainVertexPointsReversed.push_back(allTerrainVertexPoints[allTerrainVertexPoints.size() - 1 - i]);
	}
	allTerrainVertexPointsReversed.emplace_back(_renderWindow.getSize().x, _renderWindow.getSize().y);

	// -------- Insane Polygon construction
	sf::CircleShape insanePolygon(80, 50);
	insanePolygon.setPosition(400, 400);

	std::vector<Point2D> allTerrainVertexPointsCircle;
	allTerrainVertexPointsCircle.reserve(insanePolygon.getPointCount());

	for (int insanePoint = insanePolygon.getPointCount(); insanePoint > 0 ; --insanePoint)
		allTerrainVertexPointsCircle.push_back(insanePolygon.getPoint(insanePoint));

	//for (int insanePoint = 0; insanePoint < insanePolygon.getPointCount(); ++insanePoint)
	//	allTerrainVertexPointsCircle.push_back(insanePolygon.getPoint(insanePoint));

	// -------- Terrain drawing
	std::vector<Point2D>& vectorToTriangulate = allTerrainVertexPoints;

	PolygonHelper::triangulate(vectorToTriangulate, _trianglesVertices);

	for (int i = 0; i < _trianglesVertices.size(); i += 3)
	{
		sf::VertexArray newTriangle{ sf::Triangles, 3 };

		newTriangle[0].position = vectorToTriangulate[_trianglesVertices[i]];
		newTriangle[1].position = vectorToTriangulate[_trianglesVertices[i+1]];
		newTriangle[2].position = vectorToTriangulate[_trianglesVertices[i+2]];

		const sf::Color randomColor = PolygonHelper::getRandomTerrainColor();

		newTriangle[0].color = randomColor;
		newTriangle[1].color = randomColor;
		newTriangle[2].color = randomColor;

		_triangles.push_back(newTriangle);
	}
}

void Terrain::draw()
{
	//_renderWindow.draw(_convexShapeTerrain);

	for (const auto& triangle : _triangles)
	{
		_renderWindow.draw(triangle);
	}
}

void Terrain::getAllVertexPointsFromBaseImage(std::vector<Point2D>& allVertexPoints)
{
	const float windowW = static_cast<float>(_renderWindow.getSize().x);
	const float windowH = static_cast<float>(_renderWindow.getSize().y);

	const float baseImageWRatio = windowW / static_cast<float>(_baseImageTerrain.getSize().x);
	const float baseImageHRatio = windowH / static_cast<float>(_baseImageTerrain.getSize().y);

	for (int i = 0; i <= NUM_VERTEX_FOR_BASE_IMAGE; ++i)
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

