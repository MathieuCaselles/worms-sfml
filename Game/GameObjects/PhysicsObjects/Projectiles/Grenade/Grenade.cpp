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

	scene.addNewGameObjects(std::move(circleExplosion));
	scene.getPhysicsWorld().addRigidBody(*m_circleExplosion);

	// ----
	updateGrenadeActivation(false, false);
}


void Grenade::shot(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	if (isActive()) // Already spawned
		return;

	setVelocity(direction * m_launchForce);
	setPosition(position);

	updateGrenadeActivation(true, false);
}

void Grenade::onCollisionEnter(IRigidBody* rb)
{
	CircleRigidBody::onCollisionEnter(rb);

	updateGrenadeActivation(false, true);
}

void Grenade::updateGrenadeActivation(bool showGrenade, bool showExplosion)
{
	setIsActive(showGrenade);
	getPhysicsProperties().m_isActive = showGrenade;

	m_circleExplosion->setIsActive(showExplosion);
	m_circleExplosion->getPhysicsProperties().m_isActive = showExplosion;
}
