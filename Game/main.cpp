#include <Engine/Game/Game.h>

#include "Scenes/GameScene.h"
#include "Scenes/SceneEnum.h"
#include "Scenes/MainMenuScene.h"


int main()
{
    Engine::Game* game = Engine::Game::GetInstance();
    game->addScenes(new MainMenuScene(), new GameScene());
    game->setCurrentScene(ScenesEnum::MAIN_MENU);
    game->run(sf::VideoMode(1920, 1080), "Pathfinder", sf::Style::Fullscreen);
    delete game;

    return 0;
}
