#include "FragmentationBall.h"

#include "Engine/Scene/Scene.h"
#include "Engine/Utility/MathUtils.h"
#include "Engine/Utility/VectorUtils.h"

#include "ExplosionFragments/ExplosionFragment.h"

FragmentationBall::FragmentationBall(sf::CircleShape circleShape, const PhysicsProperties& properties, int numFragments)
	: Grenade(std::move(circleShape), properties),
	m_numFragments(numFragments)
{
	m_childrenFragments.resize(m_numFragments);
	if (!m_grenadeTexture.loadFromFile("Assets/Textures/Fragmentation.png"))
		throw("ERROR::MAINMENUSCENE::COULD NOT LOAD TEXTURE");
	m_grenadeShape.setTexture(&m_grenadeTexture);
	m_grenadeShape.setScale(2.0f, 2.0f);
}

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
	for (int i = 0; i < m_numFragments; ++i)
	{
		sf::CircleShape fragShape = m_grenadeShape;
		fragShape.setRadius(static_cast<int>(m_grenadeShape.getRadius() * 0.75f));
		fragShape.setOrigin(fragShape.getRadius(), fragShape.getRadius());

		auto newExplosionFrag = Engine::GameObjectFactory::create<ExplosionFragment>(fragShape, getPhysicsProperties());
		newExplosionFrag->setDamages(m_fragsDamage);
		newExplosionFrag->setDurationBeforeExplosion(m_fragsDurationBeforeExplosion);
		m_childrenFragments[i] = newExplosionFrag.get();

		scene.getPhysicsWorld().addRigidBody(*m_childrenFragments[i]);
		scene.addNewGameObjects(std::move(newExplosionFrag));
	}
}

void FragmentationBall::onCollisionEnter(IRigidBody* rb)
{
	m_circleExplosion->setDamage(m_damages);
}

void FragmentationBall::startExplosion()
{
	Grenade::startExplosion();

	for (const auto& frag : m_childrenFragments)
	{
		const auto position = sf::Vector2f(m_grenadeShape.getPosition().x, m_grenadeShape.getPosition().y - m_grenadeShape.getRadius() * 2);

		const auto randForce = static_cast<float>(MathUtils::getRandomNumber(m_fragsMinForce * 100, m_fragsMaxForce * 100)) / 100;
		const auto randAngle = MathUtils::getRandomNumber(0, m_fragsSpawnXAngleIncertitude) - m_fragsSpawnXAngleIncertitude / 2;
		const auto randDirection = randForce * VectorUtils::Normalize(VectorUtils::Rotate(sf::Vector2f(0, -1), randAngle * MathUtils::DEG_TO_RAD));

		frag->shot(position, randDirection);
	}
}

void FragmentationBall::setFragmentsForceMinMax(float minForce, float maxForce)
{
	m_fragsMinForce = minForce;
	m_fragsMaxForce = maxForce;
}