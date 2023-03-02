#include "FragmentationBall.h"

#include "Engine/Scene/Scene.h"
#include "Engine/Utility/MathUtils.h"
#include "Engine/Utility/VectorUtils.h"

#include "ExplosionFragments/ExplosionFragment.h"

FragmentationBall::FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Grenade(std::move(circleShape), properties)
{ }

void FragmentationBall::updateImplementation(const float& deltaTime, IGameObject& gameObject, Engine::IScene& scene)
{
	Grenade::updateImplementation(deltaTime, gameObject, scene);
}

void FragmentationBall::renderImplementation(IGameObject& gameObject, sf::RenderWindow& window)
{
	Grenade::renderImplementation(gameObject, window);
}

void FragmentationBall::onBeginPlay(Engine::IScene& scene)
{
	Grenade::onBeginPlay(scene);

	// ---- Create explosion shape
	for (int i = 0; i < static_cast<int>(m_childrenFragments.size()); ++i)
	{
		sf::CircleShape fragShape = m_grenadeShape;
		fragShape.setRadius(static_cast<int>(m_grenadeShape.getRadius() * 0.75f));
		fragShape.setOrigin(fragShape.getRadius(), fragShape.getRadius());

		auto newExplosionFrag = Engine::GameObjectFactory::create<ExplosionFragment>(fragShape, getPhysicsProperties());
		newExplosionFrag->setDamages(m_fragmentsDamage);
		newExplosionFrag->setDurationBeforeExplosion(m_fragmentsDurationBeforeExplosion);
		m_childrenFragments[i] = newExplosionFrag.get();

		scene.getPhysicsWorld().addRigidBody(*m_childrenFragments[i]);
		scene.addNewGameObjects(std::move(newExplosionFrag));
	}
}

void FragmentationBall::startExplosion()
{
	Grenade::startExplosion();

	for (const auto& frag : m_childrenFragments)
	{
		const auto position = sf::Vector2f(m_grenadeShape.getPosition().x, m_grenadeShape.getPosition().y - m_grenadeShape.getRadius() * 2);

		const auto randForce = static_cast<float>(MathUtils::getRandomNumber(m_fragsMinForce * 100, m_fragsMaxForce * 100)) / 100;
		const auto randAngle = MathUtils::getRandomNumber(0, 60) - 30;
		const auto randDirection = randForce * VectorUtils::Normalize(VectorUtils::Rotate(sf::Vector2f(0, -1), randAngle * MathUtils::DEG_TO_RAD));

		frag->shot(position, randDirection);
	}
}

void FragmentationBall::setFragmentsForceMinMax(float minForce, float maxForce)
{
	m_fragsMinForce = minForce;
	m_fragsMaxForce = maxForce;
}