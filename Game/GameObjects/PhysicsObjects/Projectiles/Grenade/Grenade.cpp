#include "Grenade.h"

#include "Engine/GameObject/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Game/Scenes/MainGameScene.h"

constexpr float GRENADE_EXPLOSION_RADIUS = 100;

Grenade::Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Engine::GameObject<PCGrenade, GCGrenade, ICVoid>(),
	  CircleRigidBody(circleShape, properties),
	  m_circleShape(std::move(circleShape))
{
	CircleRigidBody::updateMass();

	m_circleShape.setPosition(m_rbPosition);
}

void Grenade::onBeginPlay(Engine::IScene& scene)
{
	GameObject<PCGrenade, GCGrenade, ICVoid>::onBeginPlay(scene);

	// ---- Create explosion shape
	sf::CircleShape explosionShape(GRENADE_EXPLOSION_RADIUS);
	explosionShape.setOrigin(explosionShape.getRadius(), explosionShape.getRadius());
	explosionShape.setFillColor(sf::Color(200, 100, 100, 150));

	auto circleExplosion = Engine::GameObjectFactory::create<CircleExplosion>(explosionShape);
	m_circleExplosion = circleExplosion.get();

	scene.getPhysicsWorld().addRigidBody(*m_circleExplosion);
	scene.addNewGameObjects(std::move(circleExplosion));

	// ----
	updateGrenadeActivation(false, false);
}

void Grenade::shot(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	if (isActive())
		return; // Already spawned

	setVelocity(direction * m_launchForce);
	setPosition(position);

	updateGrenadeActivation(true, false);
}

void Grenade::startExplosion()
{
	if (hasExploded())
		return;

	updateGrenadeActivation(false, true);

	if (m_onExplosionCallback != nullptr)
		m_onExplosionCallback();
}

void Grenade::stopExplosion()
{
	updateGrenadeActivation(false, false);
}

void Grenade::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);

	if (rb->getPhysicsProperties().m_isTraversable)
		return;

	startExplosion();
}

void Grenade::updateGrenadeActivation(bool showGrenade, bool showExplosion)
{
	getPhysicsProperties().m_isActive = showGrenade;
	setIsActive(showGrenade);

	m_circleExplosion->getPhysicsProperties().m_isActive = showExplosion;
	m_circleExplosion->setIsActive(showExplosion);

	m_currentTime = 0;
}

bool Grenade::hasExploded() const
{
	return !isActive() || m_circleExplosion->isActive();
}