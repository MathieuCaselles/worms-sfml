#include "PCBlackHole.h"

#include "BlackHole.h"

void PCBlackHole::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& blackHole = reinterpret_cast<BlackHole&>(gameObject);

	//for (const auto& rb : blackHole.)
	//{
	//	rb->addForce(blackHole.m_force);
	//}
}
