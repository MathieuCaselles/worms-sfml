#include "BananaCollectible.h"

#include "Game/GameObjects/Player/Player.h"

BananaCollectible::BananaCollectible(const sf::CircleShape& circleShape)
	: Engine::GameObject<PCVoid, GCBananaCollectible, ICVoid>(), CircleRigidBody(circleShape, {}),
	m_bananaShape(circleShape)
{
	m_rbProperties.m_isTraversable = true;
	m_rbProperties.m_isStatic = true;

	hide();
}

void BananaCollectible::onCollisionEnter(IRigidBody* rb)
{
	if (const auto player = dynamic_cast<Player*>(rb); player != nullptr) // argh
	{
		player->setNumberBanana(player->getNumberBanana() + 1);

		if (m_onCollectCallback != nullptr)
			m_onCollectCallback();

		hide();
	}
}

void BananaCollectible::show(sf::Vector2f spawnPoint)
{
	if (isActive())
		return; // Has already spawned

	m_rbPosition = spawnPoint;

	m_bananaShape.setPosition(m_rbPosition);

	m_rbProperties.m_isActive = true;
	setIsActive(true);
}

void BananaCollectible::hide()
{
	m_rbProperties.m_isActive = false;
	setIsActive(false);
}