#ifndef GCVOID_H
#define GCVOID_H

#include <Engine/Components/GraphicsComponent.h>

struct GCVoid : Engine::IGraphicsComponent
{
	GCVoid();
	void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};

#endif // GCVOID_H