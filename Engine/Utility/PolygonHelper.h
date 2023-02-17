#pragma once

#include "CollisionUtils.h"
#include "Game/Assets/GameColors.h"


class PolygonHelper
{
public:
	using Point2D = sf::Vector2f;

	static bool triangulate(const std::vector<Point2D>& vertices, std::vector<int>& outTrianglesIndexes)
	{
		if(vertices.size() < 3)
			return false; // It is useless to triangulate a triangle.

		// ------

		std::vector<int> indexVector;

		indexVector.reserve(vertices.size());

		for (int i = 0; i < static_cast<int>(vertices.size()); ++i)
		{
			indexVector.push_back(i);
		}

		// ------
		const int totalTrianglesCount = static_cast<int>(vertices.size()) - 2;
		const int totalTrianglesIndexCount = totalTrianglesCount * 3;

		outTrianglesIndexes.clear();
		outTrianglesIndexes.reserve(totalTrianglesIndexCount);

		while(indexVector.size() > 3)
		{
			for (int i = 0; i < static_cast<int>(indexVector.size()); ++i)
			{
				const int currentVertexIndex = indexVector[i];
				const int previousVertexIndex = getItemSafely(indexVector, i - 1);
				const int nextVertexIndex = getItemSafely(indexVector, i + 1);

				const sf::Vector2f currentVertex = vertices[currentVertexIndex];
				const sf::Vector2f previousVertex = vertices[previousVertexIndex];
				const sf::Vector2f nextVertex = vertices[nextVertexIndex];

				const sf::Vector2f currentToPreviousVertex = previousVertex - currentVertex;
				const sf::Vector2f currentToNextVertex = nextVertex - currentVertex;

				// Is this vertex convex ? Convex vertex if cross test is greater than 0
				if(VectorUtils::Cross2D(currentToPreviousVertex, currentToNextVertex) < 0.f)
					continue;

				bool isEar = true;

				// Test if ear contains any polygon vertices
				for (int j = 0; j < vertices.size(); ++j)
				{
					if (j == currentVertexIndex || j == previousVertexIndex || j == nextVertexIndex)
						continue; // No need to iterate through current vertices

					if(CollisionUtils::pointToTriangle(vertices[j], previousVertex, currentVertex, nextVertex))
					{
						isEar = false;
						break;
					}
				}

				if(isEar)
				{
					outTrianglesIndexes.push_back(previousVertexIndex);
					outTrianglesIndexes.push_back(currentVertexIndex);
					outTrianglesIndexes.push_back(nextVertexIndex);
					indexVector.erase(indexVector.begin() + i);
					break;
				}
			}
		}

		outTrianglesIndexes.push_back(indexVector[0]);
		outTrianglesIndexes.push_back(indexVector[1]);
		outTrianglesIndexes.push_back(indexVector[2]);

		return true;
	}

	static sf::Color getRandomTerrainColor()
	{
		const auto randomRed = MathUtils::getRandomNumber(GameColors::terrainRandomTriangleColorMin.r, GameColors::terrainRandomTriangleColorMax.r);
		const auto randomBlue = MathUtils::getRandomNumber(GameColors::terrainRandomTriangleColorMin.g, GameColors::terrainRandomTriangleColorMin.g);
		const auto randomGreen = MathUtils::getRandomNumber(GameColors::terrainRandomTriangleColorMin.b, GameColors::terrainRandomTriangleColorMin.b);

		return { static_cast<sf::Uint8>(randomRed), static_cast<sf::Uint8>(randomBlue), static_cast<sf::Uint8>(randomGreen) };
	}

private:
	template<typename T>
	static T getItemSafely(const std::vector<T>& inVector, int itemIndex)
	{
		return itemIndex >= static_cast<int>(inVector.size()) ? inVector[itemIndex % inVector.size()] :
			   itemIndex < 0 ?									inVector[itemIndex + inVector.size()] :
		       inVector[itemIndex];
	}


};
