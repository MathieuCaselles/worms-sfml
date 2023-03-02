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

void ExplosionFragment::onCollisionEnter(IRigidBody* rb)
{
	Grenade::onCollisionEnter(rb);
}
