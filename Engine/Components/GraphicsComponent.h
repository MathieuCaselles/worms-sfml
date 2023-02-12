#pragma once

#include <SFML/Graphics.hpp>

namespace Engine {

class IGameObject;


struct IGraphicsComponent
{
    virtual ~IGraphicsComponent() = default;
    virtual void renderImplementation(IGameObject& gameObject, sf::RenderWindow& window) = 0;
};


}
