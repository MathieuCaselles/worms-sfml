#include "FragmentationBall.h"

#include "Engine/Scene/Scene.h"
#include "Engine/Utility/MathUtils.h"
#include "Engine/Utility/VectorUtils.h"

FragmentationBall::FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties)
	: Grenade(std::move(circleShape), properties)
{ }

void FragmentationBall::onBeginPlay(Engine::IScene& scene)
{
	Grenade::onBeginPlay(scene);

	// ---- Create explosion shape
	for (int i = 0; i < static_cast<int>(m_childrenFragments.size()); ++i)
	{
		sf::CircleShape fragShape = m_grenadeShape;
		fragShape.setRadius(static_cast<int>(m_grenadeShape.getRadius() * 1.5f));
		fragShape.setOrigin(fragShape.getRadius(), fragShape.getRadius());

		auto newExplosionFrag = Engine::GameObjectFactory::create<ExplosionFragment>(fragShape, getPhysicsProperties());
		m_childrenFragments[i] = newExplosionFrag.get();

		newExplosionFrag->getPhysicsProperties().m_isActive = false;
		newExplosionFrag->setIsActive(false);

		scene.getPhysicsWorld().addRigidBody(*m_childrenFragments[i]);
		scene.addNewGameObjects(std::move(newExplosionFrag));
	}
}

void FragmentationBall::onCollisionEnter(IRigidBody* rb)
{
	Grenade::onCollisionEnter(rb);

	for (const auto& frag : m_childrenFragments)
	{
		frag->getPhysicsProperties().m_isActive = false;
		frag->setIsActive(false);

		const auto randForce = static_cast<float>(MathUtils::getRandomNumber(1, 2));
		const auto randAngle = MathUtils::getRandomNumber(0, 60) - 30;
		const auto randDirection = VectorUtils::Normalize(VectorUtils::Rotate(sf::Vector2f(0, -1), randAngle * MathUtils::DEG_TO_RAD));

		frag->shot(sf::Vector2f(getPosition().x, getPosition().y - getRadius() * 2), randDirection);
	}
}

void FragmentationBall::setFragmentsForceMinMax(float minForce, float maxForce)
{
	m_fragsMinForce = minForce;
	m_fragsMaxForce = maxForce;
}
