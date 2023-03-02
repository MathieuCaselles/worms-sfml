#include "Scene.h"

#include "../Game/Game.h"
#include "../GameObject/GameObject.h"
namespace Engine {
	using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

	IScene::IScene() : m_window(*GameInstance::GetInstance()->getWindow())
	{
	}

	IScene::~IScene()
	{
	}


	const sf::Vector2i IScene::getMousePositionScreen()
	{
		return sf::Mouse::getPosition();
	}

	const sf::Vector2i IScene::getMousePositionWindow()
	{
		return sf::Mouse::getPosition(m_window);
	}

	const sf::Vector2f IScene::getMousePositionView()
	{
		return m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
	}



	void IScene::onBeginPlay() {
		for (const auto& pGameObject : m_gameObjects)
		{
			pGameObject->onBeginPlay(*this);
		}
	}


	void IScene::onEndPlay() {
		for (const auto& pGameObject : m_gameObjects)
		{
			pGameObject->onEndPlay(*this);
		}
	}


	void IScene::processInput(sf::Event& inputEvent)
	{
		for (const auto& pGameObject : m_gameObjects)
		{
			pGameObject->processInput(inputEvent, *this);
		}
	}

	void IScene::update(const float& deltaTime)
	{
		m_physicsWorld.step(deltaTime);

		for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); ) {
			IGameObject* gameObject = (*it).get();

			if (gameObject == nullptr || gameObject->isWaitingToBeDestroyed()) {
				gameObject->onEndPlay(*this);
				it = m_gameObjects.erase(it);
			}
			else {
				gameObject->update(deltaTime, *this);
				++it;
			}
		}

		moveNewGameObjects();
	}

	void IScene::render()
	{
		for (const auto& pGameObject : m_gameObjects)
		{
			pGameObject->render(m_window);
		}
	}
	void IScene::moveNewGameObjects()
	{
		if (!m_newGameObjects.empty())
		{
			for (auto& newGameObject : m_newGameObjects) {
				newGameObject->onBeginPlay(*this);
				m_gameObjects.push_back(std::move(newGameObject));
			}
			m_newGameObjects.clear();
		}
	}


	IGameObject* IScene::getGameObject(const size_t index)
	{
		return m_gameObjects.at(index).get();
	}

	IGameObject* IScene::findGameObject(std::function<bool(const IGameObject* gameObject)> const& condition) {
		auto it = std::find_if(m_gameObjects.begin(), m_gameObjects.end(), [condition](const std::unique_ptr<IGameObject>& gameObject) {
			return condition(gameObject.get()); 
		});
		return it != m_gameObjects.end() ? (*it).get() : nullptr;
	};


	GameObjects& IScene::getGameObjects()
	{
		return m_gameObjects;
	}

	PhysicsWorld& IScene::getPhysicsWorld()
	{
		return m_physicsWorld;
	}

	sf::RenderWindow& IScene::getWindow()
	{
		return m_window;
	}
}
