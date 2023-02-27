#pragma once


#include <Tools/DesignPatterns/Composite.h>
#include <Tools/DesignPatterns/Factory.h>

#include "../Components/InputComponent.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/GraphicsComponent.h"
#include "Engine/Utility/RTTI.h"
#include <SFML/Graphics.hpp>

namespace Engine {
	class IScene;


	class IGameObject : public Tools::Composite<IGameObject>, public HasRTTI
	{
	public:
		DECLARE_RTTI(IGameObject, NoRTTIRoot)

	public:
		virtual ~IGameObject() {};

		virtual void onBeginPlay(IScene& scene) {};
		virtual void onEndPlay(IScene& scene) {};

		virtual void processInput(sf::Event& inputEvent, IScene& scene) = 0;
		virtual void update(const float& deltaTime, IScene& scene) = 0;
		virtual void render(sf::RenderWindow& window) = 0;
	};

	template<typename... MixinGameComponents>
	class GameObject : public IGameObject, public MixinGameComponents...
	{
	public:
		DECLARE_RTTI(GameObject, IGameObject)

	public:
		void processInput(sf::Event& inputEvent, IScene& scene) override
		{
			this->processInputImplementation(*this, inputEvent, scene);
		}

		void update(const float& deltaTime, IScene& scene) override
		{
			this->updateImplementation(deltaTime, *this, scene);
		}

		void render(sf::RenderWindow& window) override
		{

			this->renderImplementation(*this, window);
		}
	};

	using AvailableGameObjectsTypes = typelist<IGameObject>;
	using GameObjectFactory = Tools::Factory<AvailableGameObjectsTypes, true>;

}
