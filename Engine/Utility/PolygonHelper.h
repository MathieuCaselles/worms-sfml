#pragma once

#include <vector>

#include "VectorUtils.h"
#include "SFML/Graphics/Color.hpp"

class PolygonHelper
{
public:
	static bool triangulate(const std::vector<sf::Vector2f>& vertices, std::vector<int>& outTrianglesIndexes);

	// Useful to find an approximated center of a polygon, calculating the mean of all the vertices position.
	static sf::Vector2f FindArithmeticMean(const std::vector<sf::Vector2f>& vertices);

	static sf::Color getRandomTerrainColor();

private:
	template<typename T>
	static T getItemSafely(const std::vector<T>& inVector, int itemIndex);
};

template <typename T>
T PolygonHelper::getItemSafely(const std::vector<T>& inVector, int itemIndex)
{
	return itemIndex >= static_cast<int>(inVector.size()) ? inVector[itemIndex % inVector.size()] :
		itemIndex < 0 ? inVector[itemIndex + inVector.size()] :
		inVector[itemIndex];
}
