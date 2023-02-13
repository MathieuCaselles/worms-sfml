#include "GCTerrain.h"

#include "Terrain.h"

void GCTerrain::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& terrain = reinterpret_cast<Terrain&>(gameObject);

	for (const auto& triangle : terrain.getTriangles())
	{
		window.draw(triangle);
	}
}
