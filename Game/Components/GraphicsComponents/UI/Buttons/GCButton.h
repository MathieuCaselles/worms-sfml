#pragma once

#include <Engine/Components/GraphicsComponent.h>


struct GCButton : Engine::IGraphicsComponent
{
	GCButton();
	virtual void renderImplementation(Engine::IGameObject& gameObject, sf::RenderWindow& window) override;
};

