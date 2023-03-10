#pragma once

#include <Engine/GameObject/GameObject.h>

#include <Game/Components/InputComponents/ICVoid.h>
#include <Game/Components/PhysicsComponents/PCVoid.h>
#include <Game/Components/GraphicsComponents/GCVoid.h>

class MapInfo : public Engine::GameObject<PCVoid, GCVoid, ICVoid>
{
public:
	DECLARE_RTTI(MapInfo, Engine::IGameObject)

public:
	MapInfo();
	~MapInfo();
private:

};