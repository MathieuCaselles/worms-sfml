#include "ICPlayer.h"

#include <Engine/Scene/Scene.h>
#include "Player.h"

ICPlayer::ICPlayer()
{
}

void ICPlayer::processInputImplementation(Engine::IGameObject& gameObject, sf::Event& inputEvent, Engine::IScene& scene)
{
	Player& button = reinterpret_cast<Player&>(gameObject);

}
