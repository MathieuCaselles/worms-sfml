#include "ExplosionFragment.h"

#include "Engine/Scene/Scene.h"

ExplosionFragment::ExplosionFragment(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Grenade(circleShape, properties)
{ }

void ExplosionFragment::onBeginPlay(Engine::IScene& scene)
{
	// ---- Create explosion shape
	sf::CircleShape explosionShape(50);
	explosionShape.setOrigin(explosionShape.getRadius(), explosionShape.getRadius());
	explosionShape.setFillColor(sf::Color(255, 130, 130, 150));

	auto circleExplosion = Engine::GameObjectFactory::create<CircleExplosion>(explosionShape);
	m_circleExplosion = circleExplosion.get();

	scene.getPhysicsWorld().addRigidBody(*m_circleExplosion);
	scene.addGameObjects(std::move(circleExplosion));

	// ----
	updateGrenadeActivation(false, false);
}

void ExplosionFragment::shot(const sf::Vector2f& position, const sf::Vector2f& direction)
{
	Grenade::shot(position, direction);
}

void ExplosionFragment::startExplosion()
{
	Grenade::startExplosion();
}

void ExplosionFragment::onCollisionEnter(IRigidBody* rb)
{
	if (dynamic_cast<ExplosionFragment*>(rb) != nullptr) // rip
		return; // We don't want to collide with others ExplosionFragment

	if (rb->getPhysicsProperties().m_isTraversable)
		return;

	Grenade::onCollisionEnter(rb);
}

void ExplosionFragment::updateImplementation(const float& deltaTime, IGameObject& gameObject, Engine::IScene& scene)
{
	Grenade::updateImplementation(deltaTime, gameObject, scene);
}

void ExplosionFragment::renderImplementation(IGameObject& gameObject, sf::RenderWindow& window)
{
	Grenade::renderImplementation(gameObject, window);
}
