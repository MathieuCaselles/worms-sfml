#include "Grenade.h"

#include "Engine/GameObject/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Utility/MathUtils.h"
#include "Game/Scenes/MainGameScene.h"

constexpr float GRENADE_EXPLOSION_RADIUS = 100;
constexpr int MIN_ANGULAR_VELOCITY_AT_SPAWN = 200;
constexpr int MAX_ANGULAR_VELOCITY_AT_SPAWN = 500;

Grenade::Grenade(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Engine::GameObject<PCGrenade, GCGrenade, ICVoid>(),
	  CircleRigidBody(circleShape, properties),
	  m_grenadeShape(std::move(circleShape))
{
	CircleRigidBody::updateMass();

	if (!m_grenadeTexture.loadFromFile("Assets/Textures/Grenade.png"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");

	m_grenadeShape.setPosition(m_rbPosition);
	m_grenadeShape.setTexture(&m_grenadeTexture);
	m_grenadeShape.setScale(2.0f, 2.0f);
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

	setVelocity(direction);
	setPosition(position);

	auto randAngularVelocity = MathUtils::getRandomNumber(MIN_ANGULAR_VELOCITY_AT_SPAWN, MAX_ANGULAR_VELOCITY_AT_SPAWN);
	randAngularVelocity = MathUtils::getRandomNumber(1, 2) == 1 ? randAngularVelocity : -randAngularVelocity;

	setAngularVelocity(randAngularVelocity);
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
	m_circleExplosion->setDamage(m_damages);
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