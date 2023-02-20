#include "GCTerrain.h"

#include "TerrainRB.h"

void GCTerrain::renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window)
{
	const auto& terrain = reinterpret_cast<TerrainRB&>(gameObject);

	for (const auto& triangle : terrain.m_triangles)
	{
		window.draw(triangle);
	}
	window.draw(terrain.m_hitSurfaceNormalLine);
}
