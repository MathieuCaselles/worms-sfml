#include <Engine/Game/Game.h>

#include "Scenes/MainGameScene.h"
#include "Scenes/MainMenuScene.h"
#include "Scenes/SceneEnum.h"

int main()
{
    Engine::Game* game = Engine::GameInstance::GetInstance();
    game->addScenes(/*new MainMenuScene(), */new MainGameScene());
    game->run(sf::VideoMode(1920, 1080), "Pathfinder", sf::Style::Default, ScenesEnum::MAIN_MENU);
    
    return 0;
}
