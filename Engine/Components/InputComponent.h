#pragma once

#include <SFML/Graphics.hpp>
namespace Engine {
    class IGameObject;
    class IScene;

    struct IInputComponent
    {
        virtual ~IInputComponent() = default;
        virtual void processInputImplementation(IGameObject& gameObject, sf::Event& inputEvent, IScene& scene) = 0;
    };
}

