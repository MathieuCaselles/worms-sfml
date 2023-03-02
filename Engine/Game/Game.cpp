#include "Game.h"
#include <cassert>
#include <memory>
#include "../Scene/Scene.h"

namespace Engine {
Game::~Game()
{
    clearScenes();
}

void Game::run(sf::VideoMode videoMode, std::string windowTitle, sf::Uint32 style, const size_t indexStartScene)
{
    m_pCurrentScene = m_scenes.at(indexStartScene);

    assert("m_pCurrentScene is nullptr", m_pCurrentScene != nullptr);

    initWindow(videoMode, windowTitle, style);

    m_pCurrentScene->onBeginPlay();

    sf::Clock DeltaTimeClock;

    while (m_window.isOpen()) {

        float deltaTime = DeltaTimeClock.restart().asSeconds();

        processInput();
        update(deltaTime);
        render();
    }
}

sf::RenderWindow* Game::getWindow()
{
    return &m_window;
}



void Game::setCurrentScene(const size_t index)
{
    m_pCurrentScene->onEndPlay();
    m_pCurrentScene = m_scenes.at(index);
    m_pCurrentScene->onBeginPlay();

}

void Game::clearScenes()
{
    for (IScene* pScene : m_scenes)
    {
        delete pScene;
    }
    m_scenes.clear();
}



// private
Game::Game()
    : m_window(sf::RenderWindow()), m_pCurrentScene(nullptr)
{
}


void Game::initWindow(sf::VideoMode videoMode, std::string windowTitle, sf::Uint32 style)
{
    m_window.create(videoMode, windowTitle, style);
    // m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(60);
}

void Game::processInput()
{

    //TODO: signal pattern instead of this
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();

        m_pCurrentScene->processInput(event);
    }
}

void Game::update(const float& deltaTime)
{
    m_pCurrentScene->update(deltaTime);
}

void Game::render()
{
    m_window.clear();
    m_pCurrentScene->render();
    m_window.display();
}
}