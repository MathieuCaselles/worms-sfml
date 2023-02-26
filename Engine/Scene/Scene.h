#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

namespace Engine {

    class IGameObject;



    class IScene
    {
        using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

    public:
        IScene();
        virtual ~IScene();

        virtual const sf::Vector2i getMousePositionScreen();
        virtual const sf::Vector2i getMousePositionWindow();
        virtual const sf::Vector2f getMousePositionView();

        virtual void onBeginPlay();
        virtual void onEndPlay();

        virtual void processInput(sf::Event& inputEvent);
        virtual void update(const float& deltaTime);
        virtual void render();

        template <typename... Args>
        void addGameObjects(Args... gameObjects);

        IGameObject* getGameObject(const size_t index);

        GameObjects& getGameObjects();

        sf::RenderWindow& getWindow();



    protected:
        sf::RenderWindow& m_window;
        GameObjects m_gameObjects;
    };
}

namespace Engine {

    template<typename ...Args>
    inline void IScene::addGameObjects(Args ...gameObjects)
    {
        (m_gameObjects.push_back(std::move(gameObjects)), ...);
    }

}
