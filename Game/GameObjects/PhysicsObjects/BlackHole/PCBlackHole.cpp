#include "PCBlackHole.h"

#include "BlackHole.h"
#include "Engine/Utility/VectorUtils.h"

void PCBlackHole::updateImplementation(const float& deltaTime, Engine::IGameObject& gameObject, Engine::IScene& scene)
{
	auto& blackHole = reinterpret_cast<BlackHole&>(gameObject);

	blackHole.m_blackHoleShape.setPosition(blackHole.m_rbPosition);

	for (const auto& rb : blackHole.m_rbsCollidingWith)
	{
		const auto direction = blackHole.getPosition() - rb->getPosition();
		const auto directionByRadius = VectorUtils::Normalize(direction) * blackHole.m_blackHoleShape.getRadius();

		if(VectorUtils::SqrMagnitude(directionByRadius) > VectorUtils::SqrMagnitude(direction))
		{
			rb->addForce((directionByRadius - direction) * blackHole.m_centerAttractionForce);
		}
	}
}
