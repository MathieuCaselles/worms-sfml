#include "CircleExplosion.h"

#include "Engine/GameObject/GameObject.h"
#include "Game/GameObjects/Player/Player.h"

CircleExplosion::CircleExplosion()
	: Engine::GameObject<PCCircleExplosion, GCCircleExplosion, ICVoid>(), CircleRigidBody(sf::CircleShape(), {})
{ }

CircleExplosion::CircleExplosion(const sf::CircleShape& circleShape)
	: Engine::GameObject<PCCircleExplosion, GCCircleExplosion, ICVoid>(), CircleRigidBody(circleShape, {}),
	m_explosionCircleShape(circleShape)
{
	CircleRigidBody::updateMass();

	m_rbProperties.m_isStatic = true;
	m_rbProperties.m_isTraversable = true;
	m_rbProperties.m_isActive = false;

	m_explosionCircleShape.setPosition(m_rbPosition);

	m_rectSourceSprite = { 0, 0, 105, 155 };

	if (!m_explosionFX.loadFromFile("Assets/Textures/VFXExplosion.png"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_spriteExplosionFX.setTexture(m_explosionFX);
	m_spriteExplosionFX.setTextureRect(m_rectSourceSprite);

	setIsActive(false);
}

void CircleExplosion::tryToPlayExplosionFX()
{
	if (m_clockForExplosionFX.getElapsedTime().asSeconds() > 0.04f && m_canPlayExplosionFX) {
		if (m_rectSourceSprite.left == 400)
		{
			m_rectSourceSprite.left = 0;
			m_canPlayExplosionFX = false;
		}
		else if (m_rectSourceSprite.left == 100)
			m_rectSourceSprite.left += 150;
		else if (m_rectSourceSprite.left == 250)
		{
			m_rectSourceSprite.left += 150;
		}
		else
		{
			m_rectSourceSprite.left += 100;
			// TODO: m_spriteExplosionFX.setScale(m_circleExplosion->getRadius(), m_circleExplosion->getRadius());
			m_spriteExplosionFX.setPosition(m_rbPosition.x - m_spriteExplosionFX.getGlobalBounds().width / 2.f,
				m_rbPosition.y - m_spriteExplosionFX.getGlobalBounds().height / 2.f);
		}
		m_spriteExplosionFX.setTextureRect(m_rectSourceSprite);
		m_clockForExplosionFX.restart();
	}
	if (!m_canPlayExplosionFX)
	{
		//m_spriteExplosionFX.setPosition(3000.f, 3000.f);
	}
}

void CircleExplosion::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);
	m_canPlayExplosionFX = true;
	if(const auto player = dynamic_cast<Player*>(rb); player != nullptr) // Very optimized way to get reference to the player
	{
		// TODO : Decrease players health
		// player->setIsActive(false);
	}
}