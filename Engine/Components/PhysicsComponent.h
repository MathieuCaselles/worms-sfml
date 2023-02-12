#pragma once

#include <SFML/Graphics.hpp>
namespace Engine {

class IGameObject;

class IScene;


struct IPhysicsComponent
{
    virtual ~IPhysicsComponent() = default;
    virtual void updateImplementation(const float& deltaTime, IGameObject& gameObject, IScene& scene) = 0;
};

}

