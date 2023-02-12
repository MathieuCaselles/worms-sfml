#pragma once
#include <list>

class PolygonHelper
{
public:
	using Point2D = sf::Vector2f;

	static bool triangulate(const std::vector<Point2D>& vertices, std::vector<int>& outTrianglesIndexes)
	{
		if(vertices.size() < 3)
			return false; // It is useless to triangulate a triangle.

		if (!isSimplePolygon(vertices) || !containsColinearEdges(vertices))
			return false;

		// ------

		std::vector<int> indexVector;

		indexVector.reserve(vertices.size());

		for (int i = 0; i < vertices.size(); ++i)
		{
			indexVector.push_back(i);
		}

		// ------
		const int totalTrianglesCount = vertices.size() - 2;
		const int totalTrianglesIndexCount = totalTrianglesCount * 3;

		outTrianglesIndexes.clear();
		outTrianglesIndexes.resize(totalTrianglesIndexCount);

		int currentTriangleIndexCount = 0;

		while(indexVector.size() > 3)
		{
			for (int i = 0; i < indexVector.size(); ++i)
			{
				const int currentVertexIndex = indexVector[i];
				const int previousVertexIndex = getItemSafely(indexVector, i - 1);
				const int nextVertexIndex = getItemSafely(indexVector, i + 1);

				sf::Vector2f currentVertex = vertices[currentVertexIndex];
				sf::Vector2f previousVertex = vertices[previousVertexIndex];
				sf::Vector2f nextVertex = vertices[nextVertexIndex];

				sf::Vector2f currentToPreviousVertex = previousVertex - currentVertex;
				sf::Vector2f currentToNextVertex = nextVertex - currentVertex;

				// Is this vertex convex ? Convex vertex if cross test is greater than 0
				if(VectorUtils::Cross(currentToPreviousVertex, currentToNextVertex) < 0.f)
					continue;

				bool isEar = true;

				// Test if ear contains any polygon vertices
				for (int j = 0; j < vertices.size(); ++j)
				{
					if (j == currentVertexIndex || j == previousVertexIndex || j == nextVertexIndex)
						continue; // No need to iterate through current vertices

					if(collisionPointToTriangle(vertices[j], previousVertex, currentVertex, nextVertex))
					{
						isEar = false;
						break;
					}
				}

				if(isEar)
				{
					outTrianglesIndexes[currentTriangleIndexCount++] = previousVertexIndex;
					outTrianglesIndexes[currentTriangleIndexCount++] = currentVertexIndex;
					outTrianglesIndexes[currentTriangleIndexCount++] = nextVertexIndex;
					indexVector.erase(indexVector.begin() + i);
				}
			}
		}

		//outTrianglesIndexes[currentTriangleIndexCount++] = indexVector[0];
		//outTrianglesIndexes[currentTriangleIndexCount++] = indexVector[1];
		//outTrianglesIndexes[currentTriangleIndexCount++] = indexVector[2];

		return true;
	}

	static bool collisionPointToTriangle(const Point2D& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c)
	{
		sf::Vector2f ab = b - a;
		sf::Vector2f bc = c - b;
		sf::Vector2f ca = a - c;

		sf::Vector2f ap = point - a;
		sf::Vector2f bp = point - b;
		sf::Vector2f cp = point - c;

		float cross1 = VectorUtils::Cross(ab, ap);
		float cross2 = VectorUtils::Cross(bc, bp);
		float cross3 = VectorUtils::Cross(ca, cp);

		return cross1 < 0.f && cross2 < 0.f && cross3 < 0.f;
	}

	static bool containsColinearEdges(const std::vector<Point2D>& vertices)
	{
		// TODO : Remove colinear edges is some exists.
		return true;
	}

	static bool isSimplePolygon(const std::vector<Point2D>& vertices)
	{
		// TODO : Make sure all of the edges doesn't cross each others.
		return true;
	}

	template<typename T>
	static T getItemSafely(const std::vector<T>& inVector, int itemIndex)
	{
		return itemIndex >= inVector.size() ? inVector[itemIndex % inVector.size()] :
			   itemIndex < 0 ?				  inVector[itemIndex % inVector.size() + inVector.size()] :
		       inVector[itemIndex];
	}

	static sf::Color getRandomTerrainColor()
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> rangeRed(170, 220);
		std::uniform_int_distribution<std::mt19937::result_type> rangeBlueGreen(60, 100);

		return { static_cast<sf::Uint8>(rangeRed(rng) + 1),
				  static_cast<sf::Uint8>(rangeBlueGreen(rng) + 1),
				   static_cast<sf::Uint8>(rangeBlueGreen(rng) + 1) };
	}
};
