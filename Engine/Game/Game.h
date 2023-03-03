#pragma once

#include <Tools/DesignPatterns/Singleton.h>
#include <SFML/Graphics.hpp>


namespace Engine {
    class IScene;

    class Game
    {
        friend class  Tools::Singleton<Game>;

    public:

        ~Game();
        void run(sf::VideoMode videoMode = sf::VideoMode(1920, 1080), std::string windowTitle = "SFML", sf::Uint32 style = sf::Style::Default, const size_t indexStartScene = 0);

        sf::RenderWindow* getWindow();

        template <typename... Args>
        void addScenes(Args... scenes);

        void setCurrentScene(const size_t index);
        void deleteSceneByIndex(const size_t index);

        void clearScenes();

    private:
        Game();
        Game(const Game&) = delete;
        // methods
        void initWindow(sf::VideoMode videoMode = sf::VideoMode(1920, 1080), std::string windowTitle = "SFML", sf::Uint32 style = sf::Style::Default);

        void processInput();
        void update(const float& deltaTime);
        void render();


        // attributes
        sf::RenderWindow m_window;

        std::vector<IScene*> m_scenes;
        IScene* m_pCurrentScene = nullptr;
    };

    template<typename ...Args>
    inline void Game::addScenes(Args ...scenes)
    {
        (m_scenes.push_back(scenes), ...);
    }

    using GameInstance = Tools::Singleton<Game>;
}