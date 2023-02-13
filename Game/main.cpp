#include <Engine/Game/Game.h>

#include "Scenes/MainGameScene.h"
#include "Scenes/SceneEnum.h"

int main()
{
    Engine::Game* game = Engine::Game::GetInstance();
    game->addScenes(new MainGameScene());
    game->setCurrentScene(ScenesEnum::MAIN_MENU);
    game->run(sf::VideoMode(1920, 1080), "Pathfinder", sf::Style::Fullscreen);

    return 0;
}
